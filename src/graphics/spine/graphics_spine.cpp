#include <spine/spine.h>
#include <spine/extension.h>

#include "graphics_texture_manager.h"

void _spAtlasPage_createTexture(spAtlasPage *self, const char *path)
{
    char name[256];
    gengine::graphics::TextureManager::simplifyName(name, path);
    auto * texture = gengine::graphics::TextureManager::getInstance().getItem(name);

    self->rendererObject = texture;
    self->width = texture->getWidth();
    self->height = texture->getHeight();
}

void _spAtlasPage_disposeTexture(spAtlasPage *self)
{
}

char *_spUtil_readFile(const char *path, int *length)
{
    return _readFile(path, length);
}
