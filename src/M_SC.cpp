#include "M_SC.h"

std::string IntToStr(int val){
    std::stringstream sssr;
    sssr<<val;
    std::string comunism=sssr.str();
    return comunism;
}

void M_SC::textscore(RenderWindow &window, Font &font)
{
    Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Magenta);
    text.setString(IntToStr(SCORE));
    text.setCharacterSize(55);
    text.setPosition((window.getView().getSize().x/2)-text.getLocalBounds().width/2,7);
    window.draw(text);
}

