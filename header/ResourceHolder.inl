template <typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename) {
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inserted.second);
}

template <typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::operator [] (Identifier id) {
    auto found = mResourceMap.find(id);
    if (found == mResourceMap.end()) {
        throw std::runtime_error("ResourceHolder::[] - resource not found");
    }
    return *(found->second);
}


template <typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::operator [] (Identifier id) const {
    auto found = this->mResourceMap.find(id);
    if (found == this->mResourceMap.end()) {
        throw std::runtime_error("ResourceHolder::get() - resource not found");
    }
    return *(found->second);
}

template class ResourceHolder<sf::Texture, Textures::ID>;
template class ResourceHolder<sf::Font, Fonts::ID>;
 