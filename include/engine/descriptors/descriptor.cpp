#include <engine/descriptors/descriptor.hpp>
#include <engine/world_object/world_object.hpp>
#include <glm/glm.hpp>

#include <engine/device_data.hpp>

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

// helper function for creating pools easily
VkDescriptorPool createPool(const DescriptorAllocator::PoolSizes& poolSizes, int count, VkDescriptorPoolCreateFlags flags) {
    std::vector<VkDescriptorPoolSize> sizes;
    sizes.reserve(poolSizes.sizes.size());
    for (auto poolSizes : poolSizes.sizes) {
        sizes.push_back({poolSizes.first, uint32_t(poolSizes.second * count)});
    }

    VkDescriptorPoolCreateInfo pool_info = {};
    pool_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    pool_info.flags = flags;
    pool_info.maxSets = count;
    pool_info.poolSizeCount = (uint32_t)sizes.size();
    pool_info.pPoolSizes = sizes.data();

    VkDescriptorPool descriptorPool;
    vkCreateDescriptorPool(_device, &pool_info, nullptr, &descriptorPool);

    return descriptorPool;
}

DescriptorBuilder DescriptorBuilder::begin(DescriptorLayoutCache* layoutCache, DescriptorAllocator* allocator) {
    DescriptorBuilder builder;
    builder.cache = layoutCache;
    builder.alloc = allocator;
    return builder;
}

DescriptorBuilder& DescriptorBuilder::bind_image(uint32_t binding, VkDescriptorImageInfo* imageInfo, VkDescriptorType type, VkShaderStageFlags stageFlags) {
    //create the descriptor binding for the layout
    VkDescriptorSetLayoutBinding newBinding{};

    newBinding.descriptorCount = 1;
    newBinding.descriptorType = type;
    newBinding.pImmutableSamplers = nullptr;
    newBinding.stageFlags = stageFlags;
    newBinding.binding = binding;

    bindings.push_back(newBinding);

    //create the descriptor write
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;

    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.dstBinding = binding;
    newWrite.pImageInfo = imageInfo;

    writes.push_back(newWrite);
    return *this;
}

DescriptorBuilder& DescriptorBuilder::bind_buffer(uint32_t binding, VkDescriptorBufferInfo* bufferInfo, VkDescriptorType type, VkShaderStageFlags stageFlags) {
    //create the descriptor binding for the layout
    VkDescriptorSetLayoutBinding newBinding{};

    newBinding.descriptorCount = 1;
    newBinding.descriptorType = type;
    newBinding.pImmutableSamplers = nullptr;
    newBinding.stageFlags = stageFlags;
    newBinding.binding = binding;

    bindings.push_back(newBinding);

    //create the descriptor write
    VkWriteDescriptorSet newWrite{};
    newWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    newWrite.pNext = nullptr;

    newWrite.descriptorCount = 1;
    newWrite.descriptorType = type;
    newWrite.pBufferInfo = bufferInfo;
    newWrite.dstBinding = binding;

    writes.push_back(newWrite);
    return *this;
}

bool DescriptorBuilder::build(VkDescriptorSet& set){
	//build layout first
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.pNext = nullptr;

        layoutInfo.pBindings = bindings.data();
        layoutInfo.bindingCount = bindings.size();

	VkDescriptorSetLayout layout = cache->create_descriptor_layout(&layoutInfo);

	//allocate descriptor
	bool success = alloc->allocate(&set, layout);
	if (!success) {return false;};

	//write descriptor
	for (VkWriteDescriptorSet& w : writes) {
		w.dstSet = set;
	}

	vkUpdateDescriptorSets(_device, writes.size(), writes.data(), 0, nullptr);

	return true;
}

bool DescriptorBuilder::build(VkDescriptorSet& set, VkDescriptorSetLayout& layout){
	//build layout first
	VkDescriptorSetLayoutCreateInfo layoutInfo{};
        layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
        layoutInfo.pNext = nullptr;

        layoutInfo.pBindings = bindings.data();
        layoutInfo.bindingCount = bindings.size();

	layout = cache->create_descriptor_layout(&layoutInfo);

	//allocate descriptor
	bool success = alloc->allocate(&set, layout);
	if (!success) {return false;};

	//write descriptor
	for (VkWriteDescriptorSet& w : writes) {
		w.dstSet = set;
	}

	vkUpdateDescriptorSets(_device, writes.size(), writes.data(), 0, nullptr);

	return true;
}

// descriptor allocator class implementation
void DescriptorAllocator::init() {}

void DescriptorAllocator::cleanup() {
    // delete every pool in both freepools and usedpools
    for (auto pool : freePools) {
        vkDestroyDescriptorPool(_device, pool, nullptr);
    }

    for (auto pool : usedPools) {
        vkDestroyDescriptorPool(_device, pool, nullptr);
    }

    currentPool = VK_NULL_HANDLE;
}

VkDescriptorPool DescriptorAllocator::grab_pool() {
    if (freePools.size() > 0) {
        VkDescriptorPool pool = freePools.back();
        freePools.pop_back();
        return pool;
    }
    else {
        return createPool(descriptorSizes, 100, 0);
    }
}

bool DescriptorAllocator::allocate(VkDescriptorSet* set, VkDescriptorSetLayout layout) {
    //initialize the currentPool handle if it's null
    if (currentPool == VK_NULL_HANDLE) {
        currentPool = grab_pool();
        usedPools.push_back(currentPool);
    }

    VkDescriptorSetAllocateInfo allocInfo = {};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pNext = nullptr;

    allocInfo.pSetLayouts = &layout;
    allocInfo.descriptorPool = currentPool;
    allocInfo.descriptorSetCount = 1;

    //try to allocate the descriptor set
    VkResult allocResult = vkAllocateDescriptorSets(_device, &allocInfo, set);
    bool needReallocate = false;

    switch (allocResult) {
    case VK_SUCCESS:
        //all good, return
        return true;
    case VK_ERROR_FRAGMENTED_POOL:
    case VK_ERROR_OUT_OF_POOL_MEMORY:
        //reallocate pool
        needReallocate = true;
        break;
    default:
        //unrecoverable error
        return false;
    }

    if (needReallocate) {
        //allocate a new pool and retry
        currentPool = grab_pool();
        usedPools.push_back(currentPool);

        allocResult = vkAllocateDescriptorSets(_device, &allocInfo, set);

        //if it still fails then we have big issues
        if (allocResult == VK_SUCCESS){
            return true;
        }
    }

    return false;
}

void DescriptorAllocator::reset_pools() {
    for (auto pool : usedPools) {
        vkResetDescriptorPool(_device, pool, 0);
        freePools.push_back(pool);
    }

    usedPools.clear();
    currentPool = VK_NULL_HANDLE;
}

// descriptor layout cache implementation
void DescriptorLayoutCache::cleanup() {
    for (auto pair : layoutCache) {
        vkDestroyDescriptorSetLayout(_device, pair.second, nullptr);
    }
}

VkDescriptorSetLayout DescriptorLayoutCache::create_descriptor_layout(VkDescriptorSetLayoutCreateInfo* info) {
    DescriptorLayoutInfo layoutInfo;
    layoutInfo.bindings.reserve(info->bindingCount);
    bool isSorted = true;
    int lastBinding = -1;

    for (int i = 0; i < info->bindingCount; i++) {
        layoutInfo.bindings.push_back(info->pBindings[i]);
        // check that bindings are in increasing order
        if (info->pBindings[i].binding > lastBinding) {
            lastBinding = info->pBindings[i].binding;
        } else {
            isSorted = false;
        }
    }

    if (!isSorted) {
        std::sort(layoutInfo.bindings.begin(), layoutInfo.bindings.end(), [](VkDescriptorSetLayoutBinding& a, VkDescriptorSetLayoutBinding& b) {
            return a.binding < b.binding;
        });
    }

    // try to find layout from cache
    auto it = layoutCache.find(layoutInfo);
    if (it != layoutCache.end()) {
        return (*it).second;
    } else {
        // create new layout, because it wasnt in the cache
        VkDescriptorSetLayout layout;
        vkCreateDescriptorSetLayout(_device, info, nullptr, &layout);

        // add layout to cache
        layoutCache[layoutInfo] = layout;
        return layout;
    }
}

bool DescriptorLayoutCache::DescriptorLayoutInfo::operator==(const DescriptorLayoutInfo& other) const{
	if (other.bindings.size() != bindings.size()){
		return false;
	}
	else {
		//compare each of the bindings is the same. Bindings are sorted so they will match
		for (int i = 0; i < bindings.size(); i++) {
			if (other.bindings[i].binding != bindings[i].binding){
				return false;
			}
			if (other.bindings[i].descriptorType != bindings[i].descriptorType){
				return false;
			}
			if (other.bindings[i].descriptorCount != bindings[i].descriptorCount){
				return false;
			}
			if (other.bindings[i].stageFlags != bindings[i].stageFlags){
				return false;
			}
		}
		return true;
	}
}

size_t DescriptorLayoutCache::DescriptorLayoutInfo::hash() const{
    using std::size_t;
    using std::hash;

    size_t result = hash<size_t>()(bindings.size());

    for (const VkDescriptorSetLayoutBinding& b : bindings)
    {
        //pack the binding data into a single int64. Not fully correct but it's ok
        size_t binding_hash = b.binding | b.descriptorType << 8 | b.descriptorCount << 16 | b.stageFlags << 24;

        //shuffle the packed binding data and xor it with the main hash
        result ^= hash<size_t>()(binding_hash);
    }

    return result;
}

// // descriptor class implementation
// void Descriptors::create_descriptor_set_layout() {
//     VkDescriptorSetLayoutBinding uboLayoutBinding{};
//         uboLayoutBinding.binding = 0;
//         uboLayoutBinding.descriptorCount = 1;
//         uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//         uboLayoutBinding.pImmutableSamplers = nullptr;
//         uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

//     VkDescriptorSetLayoutBinding samplerLayoutBinding{};
//         samplerLayoutBinding.binding = 1;
//         samplerLayoutBinding.descriptorCount = 1;
//         samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//         samplerLayoutBinding.pImmutableSamplers = nullptr;
//         samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;

//     std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
//     VkDescriptorSetLayoutCreateInfo layoutInfo{};
//     layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
//     layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
//     layoutInfo.pBindings = bindings.data();

//     if (vkCreateDescriptorSetLayout(_device, &layoutInfo, nullptr, &_descriptorSetLayout) != VK_SUCCESS) {
//         throw std::runtime_error("failed to create descriptor set layout!");
//     }
// }

// void Descriptors::create_descriptor_pool(std::vector<VkImage> swapChainImages) {
//     std::array<VkDescriptorPoolSize, 2> poolSizes{};
//         poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//         poolSizes[0].descriptorCount = static_cast<uint32_t>(swapChainImages.size());
//         poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//         poolSizes[1].descriptorCount = static_cast<uint32_t>(swapChainImages.size());

//     VkDescriptorPoolCreateInfo poolInfo{};
//         poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
//         poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
//         poolInfo.pPoolSizes = poolSizes.data();
//         poolInfo.maxSets = static_cast<uint32_t>(swapChainImages.size());

//     if (vkCreateDescriptorPool(_device, &poolInfo, nullptr, &_descriptorPool) != VK_SUCCESS) {
//         throw std::runtime_error("failed to create descriptor pool!");
//     }
// }

// void Descriptors::create_descriptor_sets(std::vector<VkImage> swapChainImages, std::vector<VkBuffer> uniformBuffers, VkImageView textureImageView, VkSampler textureSampler) {
//     std::vector<VkDescriptorSetLayout> layouts(swapChainImages.size(), _descriptorSetLayout);
//     VkDescriptorSetAllocateInfo allocInfo{};
//     allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
//     allocInfo.descriptorPool = _descriptorPool;
//     allocInfo.descriptorSetCount = static_cast<uint32_t>(swapChainImages.size());
//     allocInfo.pSetLayouts = layouts.data();

//     _descriptorSets.resize(swapChainImages.size());
//     if (vkAllocateDescriptorSets(_device, &allocInfo, _descriptorSets.data()) != VK_SUCCESS) {
//         throw std::runtime_error("failed to allocate descriptor sets!");
//     }

//     struct TestGlobalBufferObject {
//         glm::mat4 model;
//         glm::mat4 view;
//         glm::mat4 proj;
//     };

//     for (size_t i = 0; i < swapChainImages.size(); i++) {
//         VkDescriptorBufferInfo bufferInfo{};
//         bufferInfo.buffer = uniformBuffers[i];
//         bufferInfo.offset = 0;
//         bufferInfo.range = sizeof(TestGlobalBufferObject);

//         VkDescriptorImageInfo imageInfo{};
//         imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
//         imageInfo.imageView = textureImageView;
//         imageInfo.sampler = textureSampler;

//         std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

//         descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//         descriptorWrites[0].dstSet = _descriptorSets[i];
//         descriptorWrites[0].dstBinding = 0;
//         descriptorWrites[0].dstArrayElement = 0;
//         descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
//         descriptorWrites[0].descriptorCount = 1;
//         descriptorWrites[0].pBufferInfo = &bufferInfo;

//         descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
//         descriptorWrites[1].dstSet = _descriptorSets[i];
//         descriptorWrites[1].dstBinding = 1;
//         descriptorWrites[1].dstArrayElement = 0;
//         descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
//         descriptorWrites[1].descriptorCount = 1;
//         descriptorWrites[1].pImageInfo = &imageInfo;

//         vkUpdateDescriptorSets(_device, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
//     }
// }

// void Descriptors::cleanup_descriptor_set_layouts() {
//     vkDestroyDescriptorSetLayout(_device, _descriptorSetLayout, nullptr);
// }

// void Descriptors::destroy_pool() {
//     vkDestroyDescriptorPool(_device, _descriptorPool, nullptr);
// }
