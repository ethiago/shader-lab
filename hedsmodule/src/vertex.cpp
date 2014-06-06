#include "vertex.h"
#include "halfedge.h"

#include <QVariant>

using namespace heds;

Vertex::Vertex(): e_edge(NULL)
{
}

Vertex::~Vertex()
{
    e_edge = NULL;
}

const QVector4D& Vertex::geometry()const
{
    return m_geometry;
}

void Vertex::setGeometry(const QVector4D& geometry)
{
    m_geometry = geometry;
}

const HalfEdge * Vertex::edge()const
{
    return e_edge;
}

HalfEdge * Vertex::edge()
{
    return e_edge;
}

void Vertex::setEdge(HalfEdge * edge)
{
    e_edge = edge;
}

const QList<QVariant>& Vertex::attribValue(int i)const
{
    Q_ASSERT(i >=0 && i < m_attribValues.size());

    return m_attribValues[i];
}

void Vertex::setAttribValue(int i, const QList<QVariant>& value)
{
    Q_ASSERT(i >=0);

    if( i >= m_attribValues.size())
    {
        QList<QVariant> t;
        for(int j = 0; j <= i-m_attribValues.size() ; ++j)
            m_attribValues.append(t);
    }
    m_attribValues[i] = value;
}

Vertex::iterator Vertex::begin()
{
    return iterator(e_edge, e_edge);
}

Vertex::iterator Vertex::end()
{
    return iterator(e_edge, NULL);
}
