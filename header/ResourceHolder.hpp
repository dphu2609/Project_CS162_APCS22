#pragma once

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>


namespace Textures {
    enum ID {
        menuBackGround,
        rightArrow,
        leftArrow,
        pointerArrow,
        nextButton,
        nextButtonHoverred,
        prevButton,
        prevButtonHoverred,
        playButton,
        playButtonHoverred,
        pauseButton,
        pauseButtonHoverred,
        replayButton,
        replayButtonHoverred
    };
};

namespace Fonts {
    enum ID {
        ComfortaaRegular,
        FiraSansRegular,
        GreateVibesRegular,
        TiltWarpRegular,
        RobotoRegular,
        FiraMonoRegular
    };
};

template <typename Resource, typename Identifier>
class ResourceHolder {
public:
    void load(Identifier id, const std::string& filename);
    Resource& operator [] (Identifier id);
    const Resource& operator [] (Identifier id) const;
private:
    std::map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};

#include "ResourceHolder.inl"