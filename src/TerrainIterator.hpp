#ifndef TERRAINITERATOR_HPP
#define TERRAINITERATOR_HPP

/*******************************************************************************
 * Copyright 2014 GeoData <geodata@soton.ac.uk>
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License.  You may obtain a copy
 * of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *******************************************************************************/

/**
 * @file TerrainIterator.hpp
 * @brief This declares the `TerrainIterator` class
 */

#include "TerrainTile.hpp"
#include "TerrainTiler.hpp"

namespace ctb {
  class TerrainIterator;
}

/**
 * @brief This forward iterates over all `TerrainTile`s in a `TerrainTiler`
 *
 * Instances of this class take a `TerrainTiler` in the constructor and are used
 * to forward iterate over all tiles in the tiler, returning a `TerrainTile *`
 * when dereferenced.  It is the caller's responsibility to call `delete` on the
 * tile.
 */
class ctb::TerrainIterator :
  public TilerIterator
{
public:

  /// Instantiate an iterator with a tiler
  TerrainIterator(const TerrainTiler &tiler):
    TerrainIterator(tiler, tiler.maxZoomLevel(), 0)
  {}

  /// The target constructor
  TerrainIterator(const TerrainTiler &tiler, i_zoom startZoom, i_zoom endZoom):
    TilerIterator(tiler, startZoom, endZoom)
  {}

  virtual TerrainTile *
  operator*() const override {
    return static_cast<TerrainTile *>(TilerIterator::operator*());
  }
  virtual TerrainTile *
  operator*(ctb::GDALDatasetReader *reader) const {
    return (static_cast<const TerrainTiler &>(tiler)).createTile(tiler.dataset(), *(GridIterator::operator*()), reader);
  }
};

#endif /* TERRAINITERATOR_HPP */
