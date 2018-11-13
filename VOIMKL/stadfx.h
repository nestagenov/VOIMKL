///константные матрицы и их размерности, которые потом уберутся
#ifndef stadfx_H
#define stadfx_H
const int M = 3;
const int N = 9;
const int MeasurMiss = 3, TraceMiss = 3, HypoMiss = 3, HypoApprove=3;
const double constQ=1;
const double constSimilarityRate = 9; //порог для D
const double constBigNumber = 10000; //для матрицы назначения, значения которые ставим туда, где точно нет решения

#include <armadillo>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <math.h>
#include "Section.h"
#include"ResultOfScan.h"

#endif stadfx_H