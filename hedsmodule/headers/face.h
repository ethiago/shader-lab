#ifndef FACE_H
#define FACE_H

#include "halfedge.h"
#include <QVector3D>
#include <QVariant>

namespace heds{

class Face
{
    HalfEdge * e_outer;

    QList<QList<QVariant> > m_uniformValues;

public:
    Face();
    Face(const Face& f);
    ~Face();

    void setOuterEdge(HalfEdge* edge);

    HalfEdge const *  outerEdge()const;
    HalfEdge *outerEdge();

    int numberOfVertices()const;

    QVector3D getNormal()const;

    const QList<QVariant>& uniformValue(int uniformId)const;
    void setUniform(int uniformId, const QList<QVariant>& data);

    class iterator{
        HalfEdge * e_first;
        HalfEdge * base;
    public:
        iterator(){ e_first = NULL; base = NULL; }
        iterator(HalfEdge * f, HalfEdge * b){ e_first = f; base = b; }
        iterator(const iterator & it) { e_first = it.e_first; base = it.base; }

        const HalfEdge * operator*(){ return base; }

        bool operator==(const iterator& it){ return (e_first == it.e_first && base == it.base); }
        bool operator!=(const iterator& it){ return (e_first != it.e_first || base != it.base); }

        iterator & operator=(const iterator & it) { e_first = it.e_first; base = it.base; return *this; }

        iterator & operator++(){ base = base->next(); if(base==e_first) base = (HalfEdge*)0; return *this; }
    };

    iterator begin()const;
    iterator end()const;
};

}

#endif // FACE_H
