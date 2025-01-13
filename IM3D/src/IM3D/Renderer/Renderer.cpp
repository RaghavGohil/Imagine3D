#include "IM3D/Renderer/Renderer.h"

namespace IM3D
{

    Renderer::Context Renderer::context;

    void Renderer::Init()
    {

        context = Renderer::Context::OpenGL; // the default render api would be opengl
        IM3D_LOG_CORE(IM3D_INFO,"Renderer is set to OpenGL."); 
        IM3D_LOG_CORE(IM3D_INFO,"Renderer is initalized!"); 
    }

};