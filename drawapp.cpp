#include "drawapp.h"


namespace Draw
{

DrawApp :: DrawApp(sf::Event & _event) : UnitTest(_event), menuBarMap(), drawSpace(), buttonMap(), shapeFuncMap(), active(false), sm(),  page(0)
{

    //window.reset(new sf::RenderWindow( sf::VideoMode(1024,900), "UnitTest Window", sf::Style::Resize | sf::Style::Close ) );

    typedef GUI::ButtonFactory Bf;
    menuBarMap["MainMenu"] = MenuBarSPtr( new MenuBar("MainMenu", internal::Horizontal, 120, 40) );
    menuBarMap["ShapesMenu"] = MenuBarSPtr( new MenuBar("ShapesMenu", internal::Horizontal, 120, 40) );

    menuBarMap["BlockMenu"] = MenuBarSPtr( new MenuBar("BlockMenu", internal::Vertical, 120, 40) );

    menuBarMap["WireframeMenu"] = MenuBarSPtr( new MenuBar("WireframeMenu", internal::Vertical, 120, 40) );

    Bf::RegisterButton<GUI::FileTexture>();
    Bf::RegisterButton<GUI::EditTexture>();
    Bf::RegisterButton<GUI::ShapeTexture>();
    Bf::RegisterButton<GUI::RectangleTexture>();
    Bf::RegisterButton<GUI::LineTexture>();
    Bf::RegisterButton<GUI::CircleTexture>();

    Bf::RegisterButton<GUI::BlockTexture>();
    Bf::RegisterButton<GUI::TriangleTexture>();
    Bf::RegisterButton<GUI::CancelTexture>();
    Bf::RegisterButton<GUI::RhombusTexture>();
    Bf::RegisterButton<GUI::PentagonTexture>();
    Bf::RegisterButton<GUI::HexagonTexture>();
    Bf::RegisterButton<GUI::OctagonTexture>();
    Bf::RegisterButton<GUI::WireFrameTexture>();
    Bf::RegisterButton<GUI::QuadTexture>();


    buttonMap["File"] = ButtonSPtr(Bf::getButton<GUI::FileTexture>());
    buttonMap["Edit"] = ButtonSPtr(Bf::getButton<GUI::EditTexture>());    
    buttonMap["Shape"] = ButtonSPtr(Bf::getButton<GUI::ShapeTexture>());
    buttonMap["Block"] = ButtonSPtr(Bf::getButton<GUI::BlockTexture>());
    buttonMap["Wireframe"] = ButtonSPtr(Bf::getButton<GUI::WireFrameTexture>());
    buttonMap["Rectangle_b"] = ButtonSPtr(Bf::getButton<GUI::RectangleTexture>());
    buttonMap["Circle_b"] = ButtonSPtr(Bf::getButton<GUI::CircleTexture>());
    buttonMap["Triangle_b"] = ButtonSPtr(Bf::getButton<GUI::TriangleTexture>());
    buttonMap["Rhombus_b"] = ButtonSPtr(Bf::getButton<GUI::RhombusTexture>());
    buttonMap["Pentagon_b"] = ButtonSPtr(Bf::getButton<GUI::PentagonTexture>());
    buttonMap["Hexagon_b"] = ButtonSPtr(Bf::getButton<GUI::HexagonTexture>());
    buttonMap["Octagon_b"] = ButtonSPtr(Bf::getButton<GUI::OctagonTexture>());
    buttonMap["Quad_b"] = ButtonSPtr(Bf::getButton<GUI::QuadTexture>());


    buttonMap["Line_w"] = ButtonSPtr(Bf::getButton<GUI::LineTexture>());
    buttonMap["Rectangle_w"] = ButtonSPtr(Bf::getButton<GUI::RectangleTexture>());
    buttonMap["Circle_w"] = ButtonSPtr(Bf::getButton<GUI::CircleTexture>());
    buttonMap["Triangle_w"] = ButtonSPtr(Bf::getButton<GUI::TriangleTexture>());
    buttonMap["Rhombus_w"] = ButtonSPtr(Bf::getButton<GUI::RhombusTexture>());
    buttonMap["Pentagon_w"] = ButtonSPtr(Bf::getButton<GUI::PentagonTexture>());
    buttonMap["Hexagon_w"] = ButtonSPtr(Bf::getButton<GUI::HexagonTexture>());
    buttonMap["Octagon_w"] = ButtonSPtr(Bf::getButton<GUI::OctagonTexture>());
    buttonMap["Quad_w"] = ButtonSPtr(Bf::getButton<GUI::QuadTexture>());

    //Register all gui components so that they can  be loaded from xml file.
    Register<GUI::EnclosingBox>("EnclosingBox", *static_cast<EnclosingBox*>(this));
    Register<GUI::MenuBar>("MainMenu", *menuBarMap["MainMenu"] );
    Register<DrawingWindow>("DrawingWindow", drawSpace);

    Initialize();

}


void DrawApp :: Initialize()
{

    shapeFuncMap[SM::w_rectangle] = &DrawApp::DrawShape<Rectangle>;
    shapeFuncMap[SM::w_circle] = &DrawApp::DrawShape<Circle>;
    shapeFuncMap[SM::w_line] = &DrawApp::DrawShape<Line>;


    shapeFuncMap[SM::w_line] = &DrawApp::DrawShape<Line>;
    shapeFuncMap[SM::w_triangle] = &DrawApp::DrawShape<Triangle>;
    shapeFuncMap[SM::w_rectangle] = &DrawApp::DrawShape<Rectangle>;
    shapeFuncMap[SM::w_rhombus] = &DrawApp::DrawShape<Rhombus>;
    shapeFuncMap[SM::w_quad] = &DrawApp::DrawShape<Quad>;
    shapeFuncMap[SM::w_pentagon] = &DrawApp::DrawShape<Pentagon>;
    shapeFuncMap[SM::w_hexagon] = &DrawApp::DrawShape<Hexagon>;
    shapeFuncMap[SM::w_octagon] = &DrawApp::DrawShape<Octagon>;
    shapeFuncMap[SM::w_circle] = &DrawApp::DrawShape<Circle>;

    shapeFuncMap[SM::b_triangle] = &DrawApp::DrawShape<BlockTriangle>;
    shapeFuncMap[SM::b_rectangle] = &DrawApp::DrawShape<BlockRectangle>;
    shapeFuncMap[SM::b_rhombus] = &DrawApp::DrawShape<BlockRhombus>;
    shapeFuncMap[SM::b_quad] = &DrawApp::DrawShape<BlockQuad>;
    shapeFuncMap[SM::b_pentagon] = &DrawApp::DrawShape<BlockPentagon>;
    shapeFuncMap[SM::b_hexagon] = &DrawApp::DrawShape<BlockHexagon>;
    shapeFuncMap[SM::b_octagon] = &DrawApp::DrawShape<BlockOctagon>;
    shapeFuncMap[SM::b_circle] = &DrawApp::DrawShape<BlockCircle>;


    //buttonMap["Rectangle_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawRectangle);
    //buttonMap["Line_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawLine);
    //buttonMap["Circle_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawCircle);

    buttonMap["Line_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_line>);

    buttonMap["Rectangle_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_rectangle>);

    buttonMap["Triangle_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_triangle>);

    buttonMap["Quad_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_quad>);

    buttonMap["Rhombus_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_rhombus>);

    buttonMap["Pentagon_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_pentagon>);

    buttonMap["Hexagon_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_hexagon>);

    buttonMap["Octagon_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_octagon>);

    buttonMap["Circle_w"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::w_circle>);

    buttonMap["Rectangle_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_rectangle>);

    buttonMap["Triangle_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_triangle>);

    buttonMap["Quad_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_quad>);

    buttonMap["Rhombus_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_rhombus>);

    buttonMap["Pentagon_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_pentagon>);

    buttonMap["Hexagon_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_hexagon>);

    buttonMap["Octagon_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_octagon>);

    buttonMap["Circle_b"]->buttonEvents.AddEvent<ShapeManager>(&sm,&SM::DrawShape<SM::b_circle>);


     MenuBarSPtr & p = menuBarMap.at("ShapesMenu");     

    p->AddMenuItem(buttonMap["Shape"]).
            AddMenuItem(menuBarMap["BlockMenu"]).
            AddMenuItem(menuBarMap["WireframeMenu"]);


    menuBarMap["BlockMenu"]->AddMenuItem(buttonMap["Block"]).            
            AddMenuItem(buttonMap["Rectangle_b"]).
            AddMenuItem(buttonMap["Circle_b"]).
            AddMenuItem(buttonMap["Rhombus_b"]).
            AddMenuItem(buttonMap["Pentagon_b"]).
            AddMenuItem(buttonMap["Hexagon_b"]).
            AddMenuItem(buttonMap["Octagon_b"]).
            AddMenuItem(buttonMap["Quad_b"]);


    menuBarMap["WireframeMenu"]->AddMenuItem(buttonMap["Wireframe"]).
            AddMenuItem(buttonMap["Line_w"]).
            AddMenuItem(buttonMap["Rectangle_w"]).
            AddMenuItem(buttonMap["Circle_w"]).
            AddMenuItem(buttonMap["Rhombus_w"]).
            AddMenuItem(buttonMap["Pentagon_w"]).
            AddMenuItem(buttonMap["Hexagon_w"]).
            AddMenuItem(buttonMap["Octagon_w"]).
            AddMenuItem(buttonMap["Quad_w"]);

    MenuBarSPtr & q = menuBarMap.at("MainMenu");

    q->AddMenuItem(buttonMap["File"]).
            AddMenuItem(buttonMap["Edit"]).
            AddMenuItem(menuBarMap["ShapesMenu"]);


    menuBarMap["ShapesMenu"]->setBorderSize(0);
    menuBarMap["BlockMenu"]->setBorderSize(0);
    menuBarMap["WireframeMenu"]->setBorderSize(0);

    drawSpace.AttachDisplay(new DrawingPage());

    page = drawSpace.getCurrentPage();

}



void DrawApp :: ApplicationPolling()
{


    for( auto & menu : menuBarMap ) menu.second->Hover(*window);


    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::H) ) buttonMap["Rectangle_w"]->Hover(*window);

   if ( sf::Keyboard::isKeyPressed(sf::Keyboard::R) ) buttonMap["Rectangle_w"]->Press();

   if ( sf::Keyboard::isKeyPressed(sf::Keyboard::C) ) buttonMap["Circle_w"]->Press();

   if ( sf::Keyboard::isKeyPressed(sf::Keyboard::L) ) buttonMap["Line_w"]->Press();

   //MenuBar bar;

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::E) ) menuBarMap["ShapesMenu"]->Collapse();

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::B) ) menuBarMap["BlockMenu"]->Collapse();

    if ( sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) menuBarMap["WireframeMenu"]->Collapse();


   if ( sm.currentShape != SM::none ) (this->*shapeFuncMap[sm.currentShape])();

   if ( active )
   {
       DrawingPage * page = static_cast<DrawingPage*>(drawSpace.getCurrentPage());
       page->EnablePageLoop();

   }



}


void DrawApp :: SetUpEnvironment()
{
    SetUpFromXml("DrawApp.xml");
    setPosition(100,100);

}

void DrawApp :: InsidePollingImpl()
{
    ApplicationPolling();    
}

void DrawApp :: DisplayObjects()
{
    window->clear();
    window->draw(*this);
    window->display();

}



void DrawApp :: ConfigureSubElements()
{
    drawSpace.Configure();
}


void DrawApp :: draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw( drawSpace );
    target.draw( *(menuBarMap.at("MainMenu").get() ) );
}


}//EON
