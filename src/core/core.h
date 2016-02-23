#pragma once

#include <Urho3D/Engine/Application.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Graphics/Renderer.h>

namespace gengine
{
namespace core
{

bool mustQuit();

bool init(int argc, char *argv[]);
int run();
void finalize();
void update();
void setMustQuit(const bool it_must_quit);
void setUpdateFactor(const float factor);

Urho3D::Context & getContext();
Urho3D::ResourceCache & getResourceCache();
Urho3D::Renderer & getRenderer();
}
}
