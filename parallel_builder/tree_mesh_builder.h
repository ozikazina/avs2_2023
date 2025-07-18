/**
 * @file    tree_mesh_builder.h
 *
 * @author  Ondrej Vlcek <xvlcek27@stud.fit.vutbr.cz>
 *
 * @brief   Parallel Marching Cubes implementation using OpenMP tasks + octree early elimination
 **/

#ifndef TREE_MESH_BUILDER_H
#define TREE_MESH_BUILDER_H

#include "base_mesh_builder.h"
#include <vector>

class TreeMeshBuilder : public BaseMeshBuilder
{
public:
    TreeMeshBuilder(unsigned gridEdgeSize);

protected:
    unsigned marchCubes(const ParametricScalarField &field);
    float evaluateFieldAt(const Vec3_t<float> &pos, const ParametricScalarField &field);
    void emitTriangle(const Triangle_t &triangle);
    const Triangle_t *getTrianglesArray() const {
        size_t size = 0;
        for (auto &vec : mTriangles) size += vec.size();

        Triangle_t* ret = new Triangle_t[size];
        Triangle_t* dest = ret;
        for (auto &vec : mTriangles) {
            dest = std::copy(vec.begin(), vec.end(), dest);
        }

        return ret;
    }

    unsigned OctreeDescent(const ParametricScalarField &field, int depth, int sidelen, int x, int y, int z);

    std::vector<std::vector<Triangle_t>> mTriangles;
};

#endif // TREE_MESH_BUILDER_H
