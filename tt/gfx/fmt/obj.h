#pragma once

namespace tt {

class TriMesh;
class TriMeshInfo;

int obj_scan(TriMeshInfo* info, const char* fname, const char* opt="");
int obj_load(TriMesh* mesh, const char* fname, const char* opt="");
int obj_save(const TriMesh* mesh, const char* fname, const char* opt="");

}

