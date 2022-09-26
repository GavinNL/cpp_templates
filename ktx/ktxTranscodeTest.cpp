#include <ktx.h>
#include <iostream>
#include <chrono>

/**
 *
 * This example will load a KTX2 texture which requires transcoding and
 * then transcodes it into a compressed GPU texture.
 */
int main(int argc, char ** argv)
{

    // Note: to generate the ktx2 images from a jpg/png file use the following commands
    //
    //  toktx --genmipmap --t2 --bcmp  outputimage.ktx2   inputimage.png
    //
    if(argc != 2)
    {
        std::cout << "Usage: \n";
        std::cout << "   ktxTranscodeTest pathToKtx.ktx2 \n";
        exit(1);
    }

    auto fname = argv[1];
    {
        ktxTexture2* kTexture = nullptr;
        // Load the texture as is. If you used the --bcmp flag when generating the
        // texture, the texture will be in Basis Universal format
        // which then needs to be transcoded into the Compressed GPU texture that
        // is used by your specific graphics card/API
        std::cout << "Loading: " << fname << std::endl;
        {
            auto t0 = std::chrono::system_clock::now();
            auto  result = ktxTexture2_CreateFromNamedFile(fname,
                                                          KTX_TEXTURE_CREATE_NO_FLAGS | KTX_TEXTURE_CREATE_LOAD_IMAGE_DATA_BIT,
                                                          &kTexture);
            if(result != KTX_SUCCESS)
            {
                std::cout << "Error: " << ktxErrorString(result) << std::endl;
                exit(1);
            }
            auto t1 = std::chrono::system_clock::now();
            std::cout << "    Time To Load       : " << std::chrono::duration<double>(t1-t0).count() << " seconds" << std::endl;
        }

        if (ktxTexture2_NeedsTranscoding(kTexture))
        {
            uint32_t numComponents, componentByteLength;
            ktxTexture2_GetComponentInfo(kTexture, &numComponents, &componentByteLength);

            std::cout << "    isArray            : " << kTexture->isArray             << std::endl;
            std::cout << "    isCubemap          : " << kTexture->isCubemap           << std::endl;
            std::cout << "    isCompressed       : " << kTexture->isCompressed        << std::endl;
            std::cout << "    generateMipmaps    : " << kTexture->generateMipmaps     << std::endl;
            std::cout << "    baseWidth          : " << kTexture->baseWidth           << std::endl;
            std::cout << "    baseHeight         : " << kTexture->baseHeight          << std::endl;
            std::cout << "    baseDepth          : " << kTexture->baseDepth           << std::endl;
            std::cout << "    numDimensions      : " << kTexture->numDimensions       << std::endl;
            std::cout << "    numLevels          : " << kTexture->numLevels           << std::endl;
            std::cout << "    numLayers          : " << kTexture->numLayers           << std::endl;
            std::cout << "    numFaces           : " << kTexture->numFaces            << std::endl;
            std::cout << "    kvDataHead         : " << kTexture->kvDataHead          << std::endl;
            std::cout << "    kvDataLen          : " << kTexture->kvDataLen           << std::endl;
            std::cout << "    dataSize           : " << kTexture->dataSize            << std::endl;
            std::cout << "    numComponents      : " << numComponents                 << std::endl;
            std::cout << "    componentByteLength: " << componentByteLength           << std::endl;
            std::cout << "    Data Size          : " << ktxTexture_GetDataSize(ktxTexture(kTexture)) << std::endl;

            // try transcoding into differnt formats
            for(auto tf : {KTX_TTF_ETC2_RGBA,
                           KTX_TTF_BC3_RGBA,  // best format for desktop, RGBA with full alpha
                           KTX_TTF_ASTC_4x4_RGBA
                           })
            {
                // we have to make a copy of the texture because we are
                // transcoding it into multiple different formats
                // we do not need to make a copy of this if
                // we are only planning on converting it to one format
                ktxTexture2* cpy = nullptr;
                auto result = ktxTexture2_CreateCopy(kTexture, &cpy);

                if(result != KTX_SUCCESS)
                {
                    std::cout << "Error: " << ktxErrorString(result) << std::endl;
                    exit(1);
                }

                {
                    auto t0 = std::chrono::system_clock::now();
                    result = ktxTexture2_TranscodeBasis(cpy, tf, 0);
                    auto t1 = std::chrono::system_clock::now();
                    std::cout << "    Transcoding to: " << ktxTranscodeFormatString(tf) << " in " << std::chrono::duration<double>(t1-t0).count() << " seconds" << std::endl;
                }

                if(result == KTX_SUCCESS)
                {
                    //==============================================================================================
                    // these are the values that you can use to copy to the
                    // GPU
                    auto transcodedDataPointer = (void*)ktxTexture_GetData(ktxTexture(cpy));
                    std::cout << "       Transcoded Data Size   : " << ktxTexture_GetDataSize(ktxTexture(cpy)) << std::endl;
                    //==============================================================================================
                    (void)transcodedDataPointer;
                    // dont need this texture anymore
                    ktxTexture_Destroy(ktxTexture(cpy));
                }
                else
                {
                    std::cout << "       Error: " << ktxErrorString(result) << std::endl;
                }

            }


            // destroy the texture
            ktxTexture_Destroy(ktxTexture(kTexture));
            std::cout << "\n\n";
        }
    }
}
