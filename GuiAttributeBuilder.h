#ifndef GUIATTRIBUTEBUILDER_H
#define GUIATTRIBUTEBUILDER_H
#include <string>
#include "Utility.h"
#include "CMarkup/Markup.h"
#include <sstream>
#include "Traits.h"


namespace GUI
{

namespace internal {

struct Attributes
{
    typedef std::pair<int,bool> INT;
    typedef std::pair<int,bool> CHAR;
    typedef std::pair<float,bool> FLOAT;
    typedef std::pair<std::pair<float,float>, bool > FFLOAT;
    typedef std::pair<std::string,bool> STRING;

    INT Height;
    INT Width;
    FLOAT Border;
    FLOAT Margin;
    INT PosX;
    INT PosY;
    INT FillColor;
    INT TextColor;
    STRING Text;
    INT FontSize;
    CHAR TextAlignment;
    FFLOAT Scale;

};

template<typename T, bool U = true>
struct SetSizeAttributes
{
    static void Build(Attributes & att, T & obj)
    {
        if ( att.Height.second && att.Width.second )
        {            
            obj.setSize(att.Width.first, att.Height.first);
        }

    }
};

template<typename T>
struct SetSizeAttributes<T,false>
{
    static void Build(Attributes & att, T & obj)
    {

    }
};

template<typename T, bool U = true>
struct SetScaleAttributes
{
    static void Build(Attributes & att, T & obj)
    {
        if ( att.Scale.second )
        {
            obj.scale(att.Scale.first.first, att.Scale.first.second );
        }
    }
};

template<typename T>
struct SetScaleAttributes<T,false>
{
    static void Build(Attributes & att, T & obj)
    {
    }
};


template<typename T,bool U = true>
struct SetPositionAttributes
{
    static void Build(Attributes & att, T & obj)
    {
        if( att.PosX.second && att.PosY.second )
        {            
            obj.setPosition( att.PosX.first, att.PosY.first);
        }
    }

};

template<typename T, bool U = true>
struct SetColorAttributes
{
    static void Build(Attributes & att, T & obj)
    {
        int col = att.FillColor.first;
        if ( att.FillColor.second ) obj.setFillColor(sf::Color( (col & 0xff), ( (col >> 8) & 0xff), ( (col >> 8) & 0xff) ) );

    }

};

template<typename T>
struct SetColorAttributes<T,false>
{
    static void Build(Attributes & att, T & obj)
    {
        int col = att.FillColor.first;
        if ( att.FillColor.second ) obj.setColor(sf::Color( (col & 0xff), ( (col >> 8) & 0xff), ( (col >> 8) & 0xff) ));
    }

};


template<typename T, bool U = true>
struct SetTextAttributes
{
    static void Build(Attributes & att, T & obj)
    {

        if( att.FontSize.second ) obj.setFontSize(att.FontSize.first);

        if ( att.Text.second ) {std::cout << "Prev Text : " << obj.getText() << std::endl;  obj.setText(att.Text.first); }

        if ( att.TextAlignment.second )
        {
            char c = std::toupper(att.TextAlignment.first);
            internal::TextAlignment align = ( c == 'C') ? internal::Center : ( c == 'L') ? internal::Left : ( c == 'R') ? internal::Right : internal::None;
            if( align != internal::None ) obj.setTextAlignment(align);                                                                                                                                    else throw "Unrecognized Text Alignment Expecting : 'C','L' or 'R'";

        }

        if ( att.TextColor.second )
        {
            int col = att.TextColor.first;
            obj.setTextColor(sf::Color( (col & 0xff), ( (col >> 8) & 0xff), ( (col >> 8) & 0xff) ) );

        }

    }
};


template<typename T>
struct SetTextAttributes<T,false>
{
    static void Build(Attributes & att, T & obj) {}
};

/*
template<typename T>
struct SetEnclosingBoxAttributes
{



};
*/


class AttributeBuilder
{

    template<typename T>
    static void SetAttributes(Attributes & att, T & obj)
    {

        SetSizeAttributes<T,internal::HasSetSize<T>::value>::Build(att,obj);

        SetScaleAttributes<T, internal::IsScalable<T>::value>::Build(att,obj);

        //SetPositionAttributes<T>::Build(att,obj);

        SetColorAttributes<T,HasSetFillColor<T>::value >::Build(att,obj);

        SetTextAttributes<T,HasText<T>::value>::Build(att,obj);

    }

public:
    template<typename T>
    static std::pair<float,float> Build(CMarkup & xmlNode, T & obj)
    {
        std::pair<float,float> offset_pos = std::make_pair(0,0);
        std::string attrib, value;
        int j = 0;
        Attributes att;
        std::cout << "Attribute Name :  " << xmlNode.GetAttribName(j) << std::endl;
        while( !( attrib = xmlNode.GetAttribName(j) ).empty()  )
        {

            if ( ( value=xmlNode.GetAttrib(attrib) ) .empty() ) return std::make_pair(0,0);
            std::cout << "Attribute Name " << attrib << "   Value : " << value << std::endl;
            if ( attrib == "Height" )
            {
                att.Height.first = atoi( value.c_str() );
                att.Height.second = true;
            }

            else if ( attrib == "Width" )
            {
                att.Width.first = atoi( value.c_str() );
                att.Width.second = true;

            }

            else if ( attrib == "Border" )
            {
                att.Border.first = atoi( value.c_str() );
                att.Border.second = true;
            }

            else if ( attrib == "Margin" )
            {
                att.Margin.first = atoi( value.c_str() );
                att.Margin.second = true;
            }

            //Don't need to set the position with other attributes
            else if ( attrib == "XOff" )
            {
                offset_pos.first = atoi( value.c_str() );
                //att.PosX.first = atoi( value.c_str() );
                att.PosX.second = true;

            }

            else if ( attrib == "YOff" )
            {
                offset_pos.second = atoi( value.c_str() );
                //att.PosY.first = atoi( value.c_str() );
                att.PosY.second = true;

            }

            else if ( attrib == "FillColor" )
            {
                std::stringstream ss;
                ss << std::hex << value;
                ss >> att.FillColor.first;
                att.FillColor.second = true;

            }

            else if ( attrib == "Text" )
            {
                att.Text.first = value;
                att.Text.second = true;

            }

            else if ( attrib == "TextColor" )
            {
                std::stringstream ss;
                ss << std::hex << value;
                ss >> att.TextColor.first;
                att.TextColor.second = true;

            }

            else if ( attrib == "TextAlignment" )
            {
                att.TextAlignment.first = value[0];
                att.TextAlignment.second = true;
            }

            else if ( attrib == "Font" )
            {
                att.FontSize.first = atoi( value.c_str() );
                att.FontSize.second = true;
            }

            else if ( attrib == "Scale" )
            {
                std::stringstream ss(value);
                std::string token;
                if ( std::getline(ss,token,',' ) ) att.Scale.first.first = atof( token.c_str() );
                if ( std::getline(ss,token,',' ) ) att.Scale.first.second = atof( token.c_str() );
                att.Scale.second = true;
            }

            j++;
        }


        SetAttributes<T>(att,obj);
        return offset_pos;
    }


};


}//EON
}//EON
#endif // GUIATTRIBUTEBUILDER_H
