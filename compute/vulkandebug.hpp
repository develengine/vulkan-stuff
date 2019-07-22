#pragma once

#define VK_CALL(result) \
    if ((result) != VK_SUCCESS) { \
        std::cerr << "Error at line " << __LINE__ << " in " << __FILE__ << '\n'; \
        exit(-1); \
    }

#define THROW_ERROR(message) ({ \
    std::cerr << "Error at line " << __LINE__ << " in " << __FILE__ << '\n'; \
    std::cerr << message << '\n'; \
    exit(-1); \
})

inline std::string versionName(uint32_t v) {
    return std::to_string(VK_VERSION_MAJOR(v)) + "." +
           std::to_string(VK_VERSION_MINOR(v)) + "." +
           std::to_string(VK_VERSION_PATCH(v));
}

inline std::string physicalDeviceTypeName(uint32_t type) {
    switch (type) {
        case VK_PHYSICAL_DEVICE_TYPE_OTHER: return "other";
        case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return "integrated gpu";
        case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return "discrete gpu";
        case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return "virtual gpu";
        case VK_PHYSICAL_DEVICE_TYPE_CPU: return "cpu";
        default: return "undefined";
    }
}

inline void printPhysicalDeviceFeatures(VkPhysicalDeviceFeatures &features) {
    std::cout << "robustBufferAccess: ";
    if (features.robustBufferAccess) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "fullDrawIndexUint32: ";
    if (features.fullDrawIndexUint32) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "imageCubeArray: ";
    if (features.imageCubeArray) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "independentBlend: ";
    if (features.independentBlend) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "geometryShader: ";
    if (features.geometryShader) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "tessellationShader: ";
    if (features.tessellationShader) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sampleRateShading: ";
    if (features.sampleRateShading) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "dualSrcBlend: ";
    if (features.dualSrcBlend) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "logicOp: ";
    if (features.logicOp) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "multiDrawIndirect: ";
    if (features.multiDrawIndirect) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "drawIndirectFirstInstance: ";
    if (features.drawIndirectFirstInstance) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "depthClamp: ";
    if (features.depthClamp) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "depthBiasClamp: ";
    if (features.depthBiasClamp) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "fillModeNonSolid: ";
    if (features.fillModeNonSolid) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "depthBounds: ";
    if (features.depthBounds) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "wideLines: ";
    if (features.wideLines) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "largePoints: ";
    if (features.largePoints) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "alphaToOne: ";
    if (features.alphaToOne) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "multiViewport: ";
    if (features.multiViewport) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "samplerAnisotropy: ";
    if (features.samplerAnisotropy) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "textureCompressionETC2: ";
    if (features.textureCompressionETC2) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "textureCompressionASTC_LDR: ";
    if (features.textureCompressionASTC_LDR) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "textureCompressionBC: ";
    if (features.textureCompressionBC) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "occlusionQueryPrecise: ";
    if (features.occlusionQueryPrecise) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "pipelineStatisticsQuery: ";
    if (features.pipelineStatisticsQuery) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "vertexPipelineStoresAndAtomics: ";
    if (features.vertexPipelineStoresAndAtomics) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "fragmentStoresAndAtomics: ";
    if (features.fragmentStoresAndAtomics) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderTessellationAndGeometryPointSize: ";
    if (features.shaderTessellationAndGeometryPointSize) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderImageGatherExtended: ";
    if (features.shaderImageGatherExtended) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderStorageImageExtendedFormats: ";
    if (features.shaderStorageImageExtendedFormats) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderStorageImageMultisample: ";
    if (features.shaderStorageImageMultisample) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderStorageImageReadWithoutFormat: ";
    if (features.shaderStorageImageReadWithoutFormat) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderStorageImageWriteWithoutFormat: ";
    if (features.shaderStorageImageWriteWithoutFormat) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderUniformBufferArrayDynamicIndexing: ";
    if (features.shaderUniformBufferArrayDynamicIndexing) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderSampledImageArrayDynamicIndexing: ";
    if (features.shaderSampledImageArrayDynamicIndexing) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderStorageBufferArrayDynamicIndexing: ";
    if (features.shaderStorageBufferArrayDynamicIndexing) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderStorageImageArrayDynamicIndexing: ";
    if (features.shaderStorageImageArrayDynamicIndexing) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderClipDistance: ";
    if (features.shaderClipDistance) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderCullDistance: ";
    if (features.shaderCullDistance) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderFloat64: ";
    if (features.shaderFloat64) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderInt64: ";
    if (features.shaderInt64) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderInt16: ";
    if (features.shaderInt16) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderResourceResidency: ";
    if (features.shaderResourceResidency) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "shaderResourceMinLod: ";
    if (features.shaderResourceMinLod) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseBinding: ";
    if (features.sparseBinding) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidencyBuffer: ";
    if (features.sparseResidencyBuffer) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidencyImage2D: ";
    if (features.sparseResidencyImage2D) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidencyImage3D: ";
    if (features.sparseResidencyImage3D) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidency2Samples: ";
    if (features.sparseResidency2Samples) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidency4Samples: ";
    if (features.sparseResidency4Samples) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidency8Samples: ";
    if (features.sparseResidency8Samples) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidency16Samples: ";
    if (features.sparseResidency16Samples) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "sparseResidencyAliased: ";
    if (features.sparseResidencyAliased) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "variableMultisampleRate: ";
    if (features.variableMultisampleRate) std::cout << "true\n";
    else std::cout << "false\n";
    std::cout << "inheritedQueries: ";
    if (features.inheritedQueries) std::cout << "true\n";
    else std::cout << "false\n";
}

inline std::vector<std::string> queueFlagBitsNames(VkQueueFlags bits) {
    std::vector<std::string> output;
    if (bits & VK_QUEUE_GRAPHICS_BIT) output.push_back("graphics");
    if (bits & VK_QUEUE_COMPUTE_BIT) output.push_back("compute");
    if (bits & VK_QUEUE_TRANSFER_BIT) output.push_back("transfer");
    if (bits & VK_QUEUE_SPARSE_BINDING_BIT) output.push_back("sparse binding");
    if (bits & VK_QUEUE_PROTECTED_BIT) output.push_back("protected");
    return output;
}
