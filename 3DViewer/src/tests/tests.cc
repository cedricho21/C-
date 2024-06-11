#include "../3D_Viewer/model.h"
#include "gtest/gtest.h"

TEST(ModelTest, HandleVertex) {
  Model model;
  std::string line = "v 1.0 2.0 3.0";
  model.handle_vertex(line);
  ASSERT_EQ(model.getVertices().size(), 1);
  EXPECT_FLOAT_EQ(model.getVertices()[0].x, 1.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].y, 2.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].z, 3.0);
}

TEST(ModelTest, HandlePolygon) {
  Model model;
  std::string line = "f 1/1/1 2/2/2 3/3/3";
  model.handle_polygon(line);
  ASSERT_EQ(model.getPolygons().size(), 1);
  EXPECT_EQ(model.getPolygons()[0].points_indices.size(), 3);
  EXPECT_EQ(model.getPolygons()[0].points_indices[0], 0);
  EXPECT_EQ(model.getPolygons()[0].points_indices[1], 1);
  EXPECT_EQ(model.getPolygons()[0].points_indices[2], 2);
}

TEST(ModelTest, ParseObjFile) {
  std::string filename = "tests/test.obj";
  Model obj = Model::parse_obj_file(filename);
  EXPECT_EQ(obj.getVertices().size(), 4);
  EXPECT_EQ(obj.getPolygons().size(), 1);
}

TEST(ModelTest, CannotOpenFile) {
  std::string filename = "non_existent_file.obj";
  testing::internal::CaptureStderr();
  Model obj = Model::parse_obj_file(filename);
  std::string output = testing::internal::GetCapturedStderr();
  EXPECT_EQ(output, "Unable to open file: non_existent_file.obj\n");
  EXPECT_TRUE(obj.getVertices().empty());
  EXPECT_TRUE(obj.getPolygons().empty());
}

TEST(ModelTest, FreeMemory) {
  Model model;
  model.getVertices().emplace_back(1.0, 2.0, 3.0);
  model.getPolygons().emplace_back(std::vector<int>{0, 1, 2});
  model.free_memory();
  EXPECT_EQ(model.getVertices().size(), 0);
  EXPECT_EQ(model.getPolygons().size(), 0);
}

TEST(ModelTest, Scale) {
  Model model;
  model.getVertices().emplace_back(1.0, 2.0, 3.0);
  model.scale(2.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].x, 2.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].y, 4.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].z, 6.0);
}

TEST(ModelTest, MoveObj) {
  Model model;
  model.getVertices().emplace_back(1.0, 2.0, 3.0);
  model.move_obj(X, 1.0);
  model.move_obj(Y, 1.0);
  model.move_obj(Z, 1.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].x, 2.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].y, 3.0);
  EXPECT_FLOAT_EQ(model.getVertices()[0].z, 4.0);
}

TEST(ModelTest, Rotate1) {
  Model model;
  model.getVertices().emplace_back(0.0, 0.0, 0.0);
  model.rotate(90, X);
  EXPECT_EQ(model.getVertices()[0].x, 0.0);
  EXPECT_EQ(model.getVertices()[0].y, 0.0);
  EXPECT_EQ(model.getVertices()[0].z, 0.0);
}

TEST(ModelTest, Rotate2) {
  Model model;
  model.getVertices().emplace_back(0.0, 0.0, 0.0);
  model.rotate(90, Y);
  EXPECT_EQ(model.getVertices()[0].x, 0.0);
  EXPECT_EQ(model.getVertices()[0].y, 0.0);
  EXPECT_EQ(model.getVertices()[0].z, 0.0);
}

TEST(ModelTest, Rotate3) {
  Model model;
  model.getVertices().emplace_back(0.0, 0.0, 0.0);
  model.rotate(90, Z);
  EXPECT_EQ(model.getVertices()[0].x, 0.0);
  EXPECT_EQ(model.getVertices()[0].y, 0.0);
  EXPECT_EQ(model.getVertices()[0].z, 0.0);
}

TEST(ModelTest, NormalizeArray) {
  Model model;
  std::vector<float> arr = {1.0, 2.0, 3.0};
  std::vector<float> normalized_arr = model.normalize_array(arr);
  EXPECT_FLOAT_EQ(normalized_arr[0], 0.0);
  EXPECT_FLOAT_EQ(normalized_arr[1], 0.5);
  EXPECT_FLOAT_EQ(normalized_arr[2], 1.0);
}

TEST(ModelTest, MinMax) {
  float a = 1;
  float b = 2;
  EXPECT_EQ(Model::min(a, b), a);
  EXPECT_EQ(Model::max(a, b), b);
}

TEST(ModelTest, CountIndicesForPolygon) {
  Model model;
  model.getPolygons().emplace_back(std::vector<int>{0, 1, 2});
  model.getPolygons().emplace_back(std::vector<int>{3, 4, 5, 6});
  int count = model.count_indices_for_polygon();
  EXPECT_EQ(count, 7);
}

TEST(ModelTest, ObjVerticesTo1DArray) {
  Model model;
  model.getVertices().emplace_back(1.0, 2.0, 3.0);
  model.getVertices().emplace_back(4.0, 5.0, 6.0);
  std::vector<float> arr = model.obj_vertices_to_1D_array();
  ASSERT_EQ(arr.size(), 6);
  EXPECT_FLOAT_EQ(arr[0], 1.0);
  EXPECT_FLOAT_EQ(arr[1], 2.0);
  EXPECT_FLOAT_EQ(arr[2], 3.0);
  EXPECT_FLOAT_EQ(arr[3], 4.0);
  EXPECT_FLOAT_EQ(arr[4], 5.0);
  EXPECT_FLOAT_EQ(arr[5], 6.0);
}

TEST(ModelTest, ObjPolygonsTo1DArray) {
  Model model;
  model.getPolygons().emplace_back(std::vector<int>{0, 1, 2});
  model.getPolygons().emplace_back(std::vector<int>{3, 4, 5, 6});
  std::vector<int> arr = model.obj_polygons_to_1D_array();
  ASSERT_EQ(arr.size(), 14);
  EXPECT_EQ(arr[0], 0);
  EXPECT_EQ(arr[1], 1);
  EXPECT_EQ(arr[2], 1);
  EXPECT_EQ(arr[3], 2);
  EXPECT_EQ(arr[4], 2);
  EXPECT_EQ(arr[5], 0);
  EXPECT_EQ(arr[6], 3);
  EXPECT_EQ(arr[7], 4);
  EXPECT_EQ(arr[8], 4);
  EXPECT_EQ(arr[9], 5);
  EXPECT_EQ(arr[10], 5);
  EXPECT_EQ(arr[11], 6);
  EXPECT_EQ(arr[12], 6);
  EXPECT_EQ(arr[13], 3);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
