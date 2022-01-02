#pragma once

class Texture {
public:
    VkImageView _textureImageView;
    VkDeviceMemory _textureImageMemory;

    Texture(const char* texturePath, VkCommandPool commandPool, VkQueue graphicsQueue);

    void create_texture_image(const char* texturePath, VkCommandPool commandPool, VkQueue graphicsQueue);
    void create_texture_image_view();
    void transition_image_layout(VkCommandPool commandPool, VkQueue graphicsQueue, VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout);
    void cleanup();

private:
    VkImage _textureImage;
};