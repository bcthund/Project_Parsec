/*
 * Noise.cpp
 *
 *  Created on: Oct 3, 2020
 *      Author: bcthund
 */

#include <core/Noise.h>

namespace Core {

	namespace Noise {
		void * t_Noise::operator[](std::string name) {
			switch(layers[name].first) {
				case NOISE_NONE:
					return &none;
					break;
				case NOISE_SIMPLEX:
					return &simplex;
					break;
				case NOISE_PERLIN:
					return &perlin;
					break;
				case NOISE_FRACTAL:
					return &fractal;
					break;
				case NOISE_RIDGED_SIMPLEX:
					return &ridgedSimplex;
					break;
				case NOISE_RIDGED_PERLIN:
					return &ridgedPerlin;
					break;
				case NOISE_VORONOI:
					return &voronoi;
					break;
				case NOISE_BILLOW:
					return &billow;
					break;
			}
			return nullptr;
		}

		t_None &t_Noise::add(std::string name, t_None* noise) {
			int id = none.add(noise);
			layers.add(name, std::make_pair(NOISE_NONE, id));
			return *none[id];
		}

		t_Simplex &t_Noise::add(std::string name, t_Simplex* noise) {
			int id = simplex.add(noise);
			layers.add(name, std::make_pair(NOISE_SIMPLEX, id));
			return *simplex[id];
		}

		t_Perlin &t_Noise::add(std::string name, t_Perlin* noise) {
			int id = perlin.add(noise);
			layers.add(name, std::make_pair(NOISE_PERLIN, id));
			return *perlin[id];
		}

		t_Fractal &t_Noise::add(std::string name, t_Fractal* noise) {
			int id = fractal.add(noise);
			layers.add(name, std::make_pair(NOISE_FRACTAL, id));
			return *fractal[id];
		}

		t_RidgedSimplex &t_Noise::add(std::string name, t_RidgedSimplex* noise) {
			int id = ridgedSimplex.add(noise);
			layers.add(name, std::make_pair(NOISE_RIDGED_SIMPLEX, id));
			return *ridgedSimplex[id];
		}

		t_RidgedPerlin &t_Noise::add(std::string name, t_RidgedPerlin* noise) {
			int id = ridgedPerlin.add(noise);
			layers.add(name, std::make_pair(NOISE_RIDGED_PERLIN, id));
			return *ridgedPerlin[id];
		}

		t_Voronoi &t_Noise::add(std::string name, t_Voronoi* noise) {
			int id = voronoi.add(noise);
			layers.add(name, std::make_pair(NOISE_VORONOI, id));
			return *voronoi[id];
		}

		t_Billow &t_Noise::add(std::string name, t_Billow* noise) {
			int id = billow.add(noise);
			layers.add(name, std::make_pair(NOISE_BILLOW, id));
			return *billow[id];
		}




		// Get a generator by layer name, but must know the correct type
		t_None& t_Noise::getNone(std::string name) {
			return *none[layers[name].second];
		}

		t_Simplex& t_Noise::getSimplex(std::string name) {
			return *simplex[layers[name].second];
		}

		t_Perlin& t_Noise::getPerlin(std::string name) {
			return *perlin[layers[name].second];
		}

		t_Fractal& t_Noise::getFractal(std::string name) {
			return *fractal[layers[name].second];
		}

		t_RidgedSimplex& t_Noise::getRidgedSimplex(std::string name) {
			return *ridgedSimplex[layers[name].second];
		}

		t_RidgedPerlin& t_Noise::getRidgedPerlin(std::string name) {
			return *ridgedPerlin[layers[name].second];
		}

		t_Voronoi& t_Noise::getVoronoi(std::string name) {
			return *voronoi[layers[name].second];
		}

		t_Billow& t_Noise::getBillow(std::string name) {
			return *billow[layers[name].second];
		}

		t_Noise::t_Noise(Sys::Map::t_ChunkData *p) {
			parent = p;
		}

		t_Noise::~t_Noise() {
			for (auto item : none )				delete item;
			for (auto item : simplex )			delete item;
			for (auto item : perlin )			delete item;
			for (auto item : fractal )			delete item;
			for (auto item : ridgedSimplex )	delete item;
			for (auto item : ridgedPerlin )		delete item;
			for (auto item : voronoi )			delete item;
			for (auto item : billow )			delete item;
		}

	} /* namespace Noise */
} /* namespace Core */
