#pragma once

#include "widget.h"

namespace gui {

class Table : public Widget
{
    using WidgVec = std::vector<std::vector<Widget*>>;

    static constexpr auto cellWidth  = 100;
    static constexpr auto cellHeight = 20;
public:
    Table(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, int rows, int cols);

    void addChildToCell(Widget& widg, int row, int col);
    void setColWidth(int col, int width);
    void setRowHeight(int row, int height);

private:
    int countXOffset(int col);
    int countYOffset(int row);

private:
     WidgVec          m_table;
     std::vector<int> m_widths;
     std::vector<int> m_heights;
};

} /* gui namespace */