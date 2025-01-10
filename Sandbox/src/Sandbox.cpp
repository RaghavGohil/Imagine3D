#include "IM3D.h"

class Sandbox : public IM3D::Application
{
public:
private:
};

IM3D::Application* IM3D::CreateApplication()
{
    return new Sandbox();
}