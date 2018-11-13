///константные матрицы и их размерности, которые потом уберутся
#ifndef stadfx_H
#define stadfx_H

static const int M = 3;
static const int N = 9;
static const int MeasurMiss = 3, TraceMiss = 3, HypoMiss = 3, HypoApprove=3;
static const double constQ=1;
static const double constSimilarityRate = 9; //порог для D
static const double constBigNumber = 10000; //для матрицы назначения, значения которые ставим туда, где точно нет решения
static int COPIES_COUNT = 0; //счетчик для трасc

#include <armadillo>
#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <math.h>

#endif stadfx_H