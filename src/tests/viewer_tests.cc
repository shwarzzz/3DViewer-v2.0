#include "../model/viewer_model.h"
#include "gtest/gtest.h"

TEST(TestFileReader, Test_1) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("tests/test1.txt"),
               s21::WrongFileExtensionError);
}

TEST(TestFileReader, Test_2) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  s21::data res = reader->WritingDataFromFile("./tests/test1.obj");

  ASSERT_EQ(res.facets_count, 3);
  ASSERT_EQ(res.vertexes_count, 12);

  ASSERT_EQ(res.vertexes.matrix.GetRows(), 12);
  ASSERT_EQ(res.vertexes.matrix.GetColumns(), 3);

  double check_matrix[12][3] = {{1, 2, 3},       {2, 4, 5},    {5, 6, 7},
                                {5.53251, 2, 3}, {5, 99, -1},  {2, 3, 5},
                                {0.123, 11, -2}, {-2, -3, -4}, {-5, -6, -7},
                                {1, 2, 3},       {3, 2, 1},    {4, 4, 4}};

  double check_polygons[3][15] = {
      {0, 1, 2}, {10, 0, 2}, {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};

  for (unsigned long i = 0; i < res.facets_count; i++) {
    for (unsigned long j = 0; j < res.polygons[i].size(); j++) {
      ASSERT_DOUBLE_EQ(check_polygons[i][j], res.polygons[i].at(j));
    }
  }
  for (unsigned long i = 0; i < res.vertexes_count; i++) {
    for (unsigned long j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(check_matrix[i][j], res.vertexes.matrix(i, j));
    }
  }
}

TEST(TestFileReader, Test_3) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  s21::data res = reader->WritingDataFromFile("./tests/test2.obj");

  ASSERT_EQ(res.facets_count, 3);
  ASSERT_EQ(res.vertexes_count, 3);

  ASSERT_EQ(res.vertexes.matrix.GetRows(), 3);
  ASSERT_EQ(res.vertexes.matrix.GetColumns(), 3);

  double check_matrix[3][3] = {
      {-1.2344, 5.01202, 0.4412}, {1, 2, 3}, {5, 9, 6}};

  double check_polygons[3][3] = {{0, 1, 2}, {1, 0, 2}, {2, 1, 0}};

  for (unsigned long i = 0; i < res.facets_count; i++) {
    for (unsigned long j = 0; j < res.polygons[i].size(); j++) {
      ASSERT_DOUBLE_EQ(check_polygons[i][j], res.polygons[i].at(j));
    }
  }
  for (unsigned long i = 0; i < res.vertexes_count; i++) {
    for (unsigned long j = 0; j < 3; j++) {
      ASSERT_DOUBLE_EQ(check_matrix[i][j], res.vertexes.matrix(i, j));
    }
  }
}

TEST(TestFileReader, Test_4) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("./tests/test3.obj"),
               s21::FileContentError);
}

TEST(TestFileReader, Test_5) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("no_such_file.obj"),
               s21::OpenFileError);
}

TEST(TestFileReader, Test_6) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("./tests/emptyfile.obj"),
               s21::FileContentError);
}

TEST(TestFileReader, Test_7) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("./tests/test4.obj"),
               s21::FileContentError);
}

TEST(TestFileReader, Test_8) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("./tests/test5.obj"),
               s21::FileContentError);
}

TEST(TestFileReader, Test_9) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("./tests/test6.obj"),
               s21::FileContentError);
}

TEST(TestFileReader, Test_10) {
  s21::FileReader* reader = &s21::FileReader::GetInstance();
  ASSERT_THROW(reader->WritingDataFromFile("obj"),
               s21::WrongFileExtensionError);
}

TEST(TestAffineTransformations, Test_1) {
  std::string str = "./tests/test1.obj";
  s21::ViewerModel model;
  model.SetPath(str);
  model.ReadDataFromFile();
  s21::data check = model.GetDrawData();
  model.UpdateData(s21::kXMove, 1.5);
  model.UpdateData(s21::kYMove, 0.052);
  model.UpdateData(s21::kZMove, -2.2);
  s21::data res = model.GetDrawData();
  for (size_t i = 0; i < res.vertexes_count; i++) {
    ASSERT_NEAR(res.vertexes.matrix(i, 0), check.vertexes.matrix(i, 0) + 1.5,
                1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 1), check.vertexes.matrix(i, 1) + 0.052,
                1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 2), check.vertexes.matrix(i, 2) - 2.2,
                1e-7);
  }
}

TEST(TestAffineTransformations, Test_2) {
  std::string str = "./tests/test7.obj";
  s21::ViewerModel model;
  model.SetPath(str);
  model.ReadDataFromFile();
  model.UpdateData(s21::kScale, 1.5);
  double check[3][3] = {{-0.0040909, -0.0136364, 0},
                        {-0.0150000, 0.0136364, 0},
                        {0.0150000, -0.0049091, 0}};
  s21::data res = model.GetDrawData();
  for (size_t i = 0; i < res.vertexes_count; i++) {
    ASSERT_NEAR(res.vertexes.matrix(i, 0), check[i][0], 1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 1), check[i][1], 1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 2), check[i][2], 1e-7);
  }
}

TEST(TestAffineTransformations, Test_3) {
  std::string str = "./tests/test7.obj";
  s21::ViewerModel model;
  model.SetPath(str);
  model.ReadDataFromFile();
  model.UpdateData(s21::kXAngle, 60);
  model.UpdateData(s21::kYAngle, -90);
  model.UpdateData(s21::kZAngle, 360);
  double check[3][3] = {{-0.7872958, -0.4545455, 0.2727273},
                        {0.7872958, 0.4545455, 1},
                        {-0.2834265, -0.1636364, -1}};
  s21::data res = model.GetDrawData();
  for (size_t i = 0; i < res.vertexes_count; i++) {
    ASSERT_NEAR(res.vertexes.matrix(i, 0), check[i][0], 1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 1), check[i][1], 1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 2), check[i][2], 1e-7);
  }
}

TEST(TestAffineTransformations, Test_4) {
  std::string str = "./tests/test7.obj";
  s21::ViewerModel model;
  model.SetPath(str);
  model.ReadDataFromFile();
  model.UpdateData(s21::kXMove, 1);
  model.UpdateData(s21::kYMove, -0.44);
  model.UpdateData(s21::kZMove, 0);
  model.UpdateData(s21::kScale, 0.65);
  model.UpdateData(s21::kXAngle, 120);
  model.UpdateData(s21::kYAngle, -49);
  model.UpdateData(s21::kZAngle, 3);
  double check[3][3] = {{0.3512842, 0.2416705, -1.0067211},
                        {0.3562101, 0.2360115, -0.9964387},
                        {0.3592716, 0.2401956, -1.0108159}};
  s21::data res = model.GetDrawData();
  for (size_t i = 0; i < res.vertexes_count; i++) {
    ASSERT_NEAR(res.vertexes.matrix(i, 0), check[i][0], 1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 1), check[i][1], 1e-7);
    ASSERT_NEAR(res.vertexes.matrix(i, 2), check[i][2], 1e-7);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}