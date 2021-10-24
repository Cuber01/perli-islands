#include <libnoise/noise.h>
#include "noiseutils.h"

#include "main.hpp"

using namespace noise;


// --------------- Modules and Maps ---------------

// lumpy terrain
module::Billow baseFlatTerrain;

// flatten baseFlatTerrain
module::ScaleBias flatTerrain;

// erratic terrain
module::RidgedMulti mountainTerrain;


// height map
utils::NoiseMap heightMap;

// heightMapBuilder
utils::NoiseMapBuilderPlane heightMapBuilder;

// --------------- Image Rendering ---------------

utils::RendererImage renderer;
utils::Image image;

module::Perlin terrainType;

module::Select finalTerrain;

// --------------- Explaining LibNoise functions ---------------
//
// SetOctaveCount(1-6) - Octaves control the amount of detail, every octave doubles the frequency of the last one. 
//
// SetFrequency(1-16) - Frequency means how many "waves" do we generate per unit length. Big frequency = tons of small islands.
//
// SetPersistence(0-1) - A multiplier that determines how quickly the amplitudes change for each successive octave. Bigger frequency means more "fuzzy" waves.
//
//
//
// -------------------------------------------------------------


void setupTerrain()
{

    // setup mountainTerrain
    mountainTerrain.SetOctaveCount(6);
    mountainTerrain.SetFrequency(1);

    // setup baseFlatTerrain
    baseFlatTerrain.SetFrequency(2.0);

    // flatten baseFlatTerrain and store it in flatTerrain
    flatTerrain.SetSourceModule(0, baseFlatTerrain);   
    flatTerrain.SetScale(0.125);
    flatTerrain.SetBias(-0.75);

    // setup terrainType
    terrainType.SetFrequency(0.5);
    terrainType.SetPersistence(0.25);

    // setup finalTerrain
    finalTerrain.SetSourceModule(0, flatTerrain); // setup layer 1
    finalTerrain.SetSourceModule(1, mountainTerrain); // setup layer 2

    finalTerrain.SetControlModule(terrainType); // merge two layers according to terrainType to create "biomes"

    // wrap up finalTerrain
    finalTerrain.SetEdgeFalloff(0.125);
    finalTerrain.SetBounds(0.0, 1000.0);

}

void setupMapBuilder()
{
    heightMapBuilder.SetSourceModule(finalTerrain);
    heightMapBuilder.SetDestNoiseMap(heightMap);

    heightMapBuilder.SetDestSize (600, 600);
    heightMapBuilder.SetBounds(0.0, 15.0, 0.0, 15.0);
}

void setupRenderer()
{
    renderer.SetSourceNoiseMap(heightMap);
    renderer.SetDestImage(image);

    renderer.ClearGradient ();
    renderer.AddGradientPoint (-1.00, utils::Color ( 32, 160,   0, 255)); // grass
    renderer.AddGradientPoint (-0.25, utils::Color (224, 224,   0, 255)); // dirt
    renderer.AddGradientPoint ( 0.25, utils::Color (128, 128, 128, 255)); // rock
    renderer.AddGradientPoint ( 1.00, utils::Color (255, 255, 255, 255)); // snow

    renderer.EnableLight();
    renderer.SetLightBrightness(1.8);

}


int main(int argc, char *argv[])
{

    setupTerrain();

    setupMapBuilder();

    setupRenderer();

    heightMapBuilder.Build();

    renderer.Render();

    utils::WriterBMP writer;
    writer.SetSourceImage(image);
    writer.SetDestFilename("test.bmp");
    writer.WriteDestFile();

	return 0;
}

























// trash


// renderer.ClearGradient ();
// renderer.AddGradientPoint (-1.0000, utils::Color (  0,   0, 128, 255)); // deeps
// renderer.AddGradientPoint (-0.2500, utils::Color (  0,   0, 255, 255)); // shallow
// renderer.AddGradientPoint ( 0.0000, utils::Color (  0, 128, 255, 255)); // shore
// renderer.AddGradientPoint ( 0.0625, utils::Color (240, 240,  64, 255)); // sand
// renderer.AddGradientPoint ( 0.1250, utils::Color ( 32, 160,   0, 255)); // grass
// renderer.AddGradientPoint ( 0.3750, utils::Color (224, 224,   0, 255)); // dirt
// renderer.AddGradientPoint ( 0.7500, utils::Color (128, 128, 128, 255)); // rock
// renderer.AddGradientPoint ( 1.0000, utils::Color (255, 255, 255, 255)); // snow
