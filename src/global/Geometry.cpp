#include "global/Geometry.hpp"

using namespace Geometry;

void Geometry::createUVSphere(int stackNum, int sliceNum, double radius, GenericGeometry* gen)
{
    gen->vertices.clear();
    gen->indices.clear();

    stackNum++;
    sliceNum++;

    for(int stack = 0; stack <= stackNum; stack++) {
        for(int slice = 0; slice <= sliceNum; slice++) {
            GeometryVertex vertex;

            vertex.texCoord = {
                slice / (double) sliceNum,
                1.0 - (stack / (double) stackNum)
            };

            double z = 1.0 - vertex.texCoord.y * 2.0;
            double theta = vertex.texCoord.x * M_PI * 2;

            double d;
            if(stack == 0 || stack == stackNum) {
                d = 0.0;
            } else {
                d = sqrt(1.0 - z * z);
            }

            vertex.position = {
                radius * cos(theta) * d,
                radius * sin(theta) * d,
                radius * z
            };

            gen->vertices.push_back(vertex);
        }
    }

    for(int stack = 0; stack < stackNum; stack++) {
        int i = stack * (sliceNum + 1);

        for(int slice = 0; slice < sliceNum; slice++) {
            if(stack != 0 && stack != stackNum) {
                gen->indices.push_back(slice + i);
                gen->indices.push_back(slice + i + sliceNum + 1);
                gen->indices.push_back(slice + i + 1);
            }

            gen->indices.push_back(slice + i + 1);
            gen->indices.push_back(slice + i + sliceNum + 1);
            gen->indices.push_back(slice + i + sliceNum + 2);
        }
    }
}
