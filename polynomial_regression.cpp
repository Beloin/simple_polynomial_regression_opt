//
// Created by beloin on 08/12/2021.
//

#include "gauss_method.cpp"
#include "utils.cpp"


/**
 * Use this function to find coefficients for the X -> Y polynomial regression.
 * @param mx Matrix ixj, being i>0 and j=2
 *
 * @param buffer
 */
void find_coefficients(int arr_size, float *mx, int degree, float *buffer);
/**
 * Predict using coefficients and a new x_value
 * Function is something like: F(X) = a0 + a1X + a2*X²
 * @param coefficients [a0, a1, a2, ...]
 * @param x_value
 * @return
 */
float predict(int arr_size, const float *coefficients, float x_value);

/**
 * Specific function to sum and elevate x to inject into augmented matrix.
 * @param x
 * @param size
 * @param degree
 * @return
 */
float elevate_and_sum_all(float *x, int size, int degree);
/**
 * Specific function to sum y values to inject into augmented matrix.
 * @param y
 * @param x
 * @param size
 * @param x_degree
 * @return value of the sum function (E(y*X^n))
 */
float sum_y(const float y[], const float x[], int size, int x_degree);
/**
 * Retrieve x and y from matrix.
 * @param arr_size
 * @param arr
 * @param inject_matrix
 */
void find_x_y(int arr_size, float *arr, float *inject_matrix);
/**
 * Private function that calculate the coefficients from x,y and degree.
 * @param x
 * @param y
 * @param degree
 * @param arr_size
 * @param buffer
 */
void calculate_coef(float x[], float y[], int degree, int arr_size, float *buffer);

void find_coefficients(int arr_size, float *mx, int degree, float *buffer) {
    float *x, *y, res[2][arr_size];
    find_x_y(arr_size, mx, &res[0][0]);
    x = res[0];
    y = res[1];
    calculate_coef(x, y, degree, arr_size, buffer);
}

void calculate_coef(float x[], float y[], int degree, int arr_size, float *buffer) {
    int quantity = degree+1, i, ii, elevate_by;
    float x_result[quantity][quantity], y_result[1][quantity];
    for (i=0; i<quantity; i++){
        for (ii=0; ii < quantity; ii++){
            elevate_by= i + ii;
            float value = elevate_and_sum_all(x, arr_size, elevate_by);
            x_result[i][ii] = value;
        }
        elevate_by = i;
        y_result[0][i] = sum_y(y, x, arr_size, elevate_by);
    }
    x_result[0][0] = (float) arr_size;
    gauss_method(quantity, &x_result[0][0], &y_result[0][0], buffer);
}

float predict(int arr_size, const float *coefficients, float x_value) {
    int i;
    float a, res = 0;
    for (i = 0; i < arr_size; ++i) {
        a = coefficients[i];
        res += a * elevate_by(x_value, i);
    }
    return res;
}

/*
 * Example:
 * [ [1,6], [2, 7] ] -> x = [1, 2]; y = [6, 7]
 */
void find_x_y(int arr_size, float *arr, float *inject_matrix){
    int i;
    float x[arr_size], y[arr_size];
    for (i = 0; i < arr_size; i++){
        float get1 = get_from_flattened_matrix(i, 0, 2, arr);
        x[i] = get1;
        float get2 = get_from_flattened_matrix(i, 1, 2, arr);
        y[i] = get2;
    }
    for (int j = 0; j < arr_size; ++j) {
        set_item_flattened_matrix(0, j, arr_size, inject_matrix, x[j]);
        set_item_flattened_matrix(1, j, arr_size, inject_matrix, y[j]);
    }
}


float sum_y(const float y[], const float x[], int size, int x_degree){
    float res = 0, temp_x, temp_y;
    for (int i = 0; i < size; ++i) {
        temp_x = x[i];
        temp_y = y[i];
        temp_x = elevate_by(temp_x, x_degree);
        res += temp_x * temp_y;
    }
    return res;
}

float elevate_and_sum_all(float *x, int size, int degree){
    float res = 0, temp;
    for (int i = 0; i < size; ++i) {
        temp = x[i];
        res += elevate_by(temp, degree);
    }
    return res;
}

