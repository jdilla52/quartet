//
// Created by Jacques Perrault on 10/18/21.
//
#include "tet_mesh.h"
#include "iostream"
#include "fstream"
#ifndef QUARTET_SRC_WRITEUGRID_H_
#define QUARTET_SRC_WRITEUGRID_H_

class TetMeshUGridWriter {
 public:
  TetMesh _tetMesh;
  std::vector<Vec3i> boundaryFaces;
  std::vector<int> boundaryPoints;
  std::ofstream _ofs;
  TetMeshUGridWriter(const TetMesh& tet_mesh, const std::string& file) {
    this->_ofs.open(file);
    _tetMesh = tet_mesh;
    tet_mesh.getBoundary(boundaryPoints, boundaryFaces);
    this->Run();
  }
  ~TetMeshUGridWriter(){
    this->_ofs.close();
  }
 public:
  void
  Run() {

    //Write header: #pt #tri #quad #tet #pyr #pri #hex
    this->_ofs << this->_tetMesh.verts().size() << " " <<
               this->boundaryFaces.size() << " 0 " <<
               this->_tetMesh.tets().size() << " 0 0 0\n";

    std::cout<< "Number of boundary faces : " << this->boundaryFaces.size() << std::endl;
    //Write points
    int count = 0;
    this->_ofs << std::scientific << std::setprecision(15);
    for (auto node : this->_tetMesh.verts()) {
      auto v = node.v;
      this->_ofs <<
                 std::setw(24) << v[0] << " " <<
                 std::setw(24) << v[1] << " " <<
                 std::setw(24) << v[2] << "\n";
    }

    //Write boundary triangles
    for (auto tri : this->boundaryFaces) {
      count++;
      auto fTri = tri.v;
      // Do the ids reference the ori
      //FIXME: Need to re-order the nodes on output
      this->_ofs <<
                 fTri[0] + 1 << " " <<
                 fTri[1] + 1 << " " <<
                 fTri[2] + 1 << "\n";
    }

    std::cout << "Number of written faces :" << count << std::endl;
    for (auto tri : this->boundaryFaces) {
      this->_ofs << 1 << "\n";
    }
    //Write boundary tags
//    auto bdyTagsMap = GenerateBoundaryTagsMap();
//    for (auto *tri : *this->qBoundaryMesh()->CellSet()) {
//      if constexpr(BoundaryCellsHaveTags)
//      {
//        auto hasher = std::hash<BoundaryCellType::TagType>{};
//        this->_ofs << bdyTagsMap[hasher(tri->Tag())].Tag << "\n";
//      }
//      else {
//        this->_ofs << 1 << "\n";
//      }
//    }

    //Write tetrahedra
    for (const auto tet : this->_tetMesh.tets()) {
      this->_ofs <<
                 tet[0] + 1 << " " <<
                 tet[1] + 1 << " " <<
                 tet[2] + 1 << " " <<
                 tet[3] + 1 << "\n";
    }

//    //Write mapbc file if applicable
//    if constexpr(BoundaryCellsHaveTags)
//    {
//      auto bdyMesh = this->qBoundaryMesh();
//      auto bcFilePath = this->_filePath;
//      bcFilePath.replace_extension(".mapbc");
//      std::ofstream bcOfs(bcFilePath);
//      bcOfs << std::setw(12) << bdyTagsMap.size() << "\n";
//      for (auto&&[tagHash, surfTagRef] : bdyTagsMap) {
//        bcOfs << std::setw(7) << surfTagRef.Tag << std::setw(7) << 0 <<
//              std::setw(6) << ' ' << bdyMesh->Cell(surfTagRef.CellId)->Tag() << "\n";
//      }
//    }
  }


//template <typename TMesh>
//std::unordered_map<std::size_t, typename TetMeshUGridWriter<TMesh>::SurfaceTagReference>
//TetMeshUGridWriter<TMesh>::GenerateBoundaryTagsMap()
//{
//  std::unordered_map<std::size_t, SurfaceTagReference> ret;
//  if constexpr (BoundaryCellsHaveTags) {
//    std::hash<BoundaryCellType::TagType> hasher;
//    std::size_t curMap = 1;
//    for (auto* tri : *this->qBoundaryMesh()->CellSet()) {
//      auto result = ret.try_emplace(hasher(tri->Tag()),
//                                    SurfaceTagReference{curMap, tri->Id()});
//      if (result.second) {
//        ++curMap;
//      }
//    }
//  }
//  return ret;
//}
};

#endif //QUARTET_SRC_WRITEUGRID_H_
