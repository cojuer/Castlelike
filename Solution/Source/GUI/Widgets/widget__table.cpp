#include "widget__table.h"

#include "utils.h"

namespace gui {

Table::Table(const std::string& name, Widget* parent, SDL_Rect geometry, bool visible, int rows, int cols) :
    Widget(name, parent, geometry, visible)
{
    m_opts["rows"] = rows;
    m_opts["cols"] = cols;
    m_table.resize(rows);
    for (auto& row : m_table)
    {
        row.resize(cols);
    }
    m_widths.resize(cols, cellWidth);
    m_heights.resize(rows, cellHeight);
}

void Table::addChildToCell(Widget& widg, int row, int col)
{
    utils::logassert(row < m_opts.at("rows"), "add child to inexistent row");
    utils::logassert(col < m_opts.at("cols"), "add child to inexistent col");

    m_table[row][col] = &widg;
    auto xOffset = countXOffset(col); 
    auto yOffset = countYOffset(row);
    widg.setPosition({ xOffset, yOffset });
    Widget::addChild(widg);
}

void Table::setColWidth(int col, int width)
{
    utils::logassert(col < m_opts.at("cols"), "set inexistent col width");

    m_widths[col] = width;

    if (m_children.empty()) return;
    for (auto& row : m_table)
    {
        for (size_t i = 0; i < row.size(); ++i)
        {
            if (row[i])
            {
                auto newPos = row[i]->getPos();
                row[i]->setPosition({ countXOffset(i), newPos.y });
            }
        }
    }
}

void Table::setRowHeight(int row, int height) 
{
    utils::logassert(row < m_opts.at("rows"), 
                     "set inexistent row width");

    m_heights[row] = height;

    if (m_children.empty()) return;
    for (size_t i = 0; i < m_table.size(); ++i)
    {
        for (auto elem : m_table[i])
        {
            if (elem)
            {
                auto newPos = elem->getPos();
                elem->setPosition({ newPos.x, countYOffset(i) });
            }
        }
    }
}

int Table::countXOffset(int col)
{
    auto xOffset = 0;
    for (auto counter = 0; counter < col; ++counter)
    {
        xOffset += m_widths[counter];
    }
    return xOffset;
}

int Table::countYOffset(int row)
{
    auto yOffset = 0;
    for (auto counter = 0; counter < row; ++counter)
    {
        yOffset += m_heights[counter];
    }
    return yOffset;
}

} /* gui namespace. */