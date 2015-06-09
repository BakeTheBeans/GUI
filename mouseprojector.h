#ifndef MOUSEPROJECTOR_H
#define MOUSEPROJECTOR_H
#include <SFML/Graphics/VertexArray.hpp>

namespace  sf {
class Window;
}

namespace  Draw {


class MouseProjector : public sf::Drawable
{

    //static bool init;
    bool flag;
    sf::VertexArray xProjection;
    sf::VertexArray yProjection;
private:
    void BuildProjectionLines();
    MouseProjector();
public:
    static MouseProjector & getMouseProjector();
    void Project(sf::Window & window);
    void EnableProjection() { flag = true; }
    void DisableMouseProjection() { flag = false; }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

}//EON
#endif // MOUSEPROJECTOR_H
