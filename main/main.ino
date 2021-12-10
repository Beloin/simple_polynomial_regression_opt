// Utils

/**
 * Elevate number by x value.
 * @param num
 * @param by
 * @return
 */
float elevate_by(float num, int by);
/**
 * Print an array.
 * @param arr
 * @param arr_size
 */
void print_arr(float *arr, int arr_size);
/**
 * Print matrix.
 * @param i
 * @param j
 * @param arr
 */
void print_matrix(int i, int j, int width, float *arr);

/**
 * Gets item from flattened matrix by given `i` and `j`.
 * @param i
 * @param j
 * @param mx
 * @return
 */
float get_from_flattened_matrix(int i, int j, int width, float *mx);

/**
 * Sets item to flattened matrix by given `i` and `j`.
 * @param i
 * @param j
 * @param mx
 * @return
 */
void set_item_flattened_matrix(int i, int j, int width, float *mx, float value);


// Polynomial

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


// Gauss

/**
 * Calculates the result of the linear system by given a and b, resulting into the augmented matrix.
 * @param arr_size
 * @param a
 * @param b
 * @param buffer where is injected the results of the linear system. With size arr_size+1
 */
void gauss_method(int arr_size, float *a, float *b, float *buffer);
/**
 * Calculates the result of the linear system given an unique matrix.
 * @param n
 * @param mx
 * @param inject
 */
void gauss_method_unique_mx(int n, float *mx, float *inject);

/**
 * Joins a and b into one unique augmented matrix, being always [n][n+1]
 * @param n
 * @param mx_a
 * @param mx_b
 * @param inject_mx
 */
void join_mx(int n, float *mx_a, float *mx_b, float *inject_mx);
/**
 * Transforms matrix into Triangle format.
 * @param n
 * @param mx
 */
void convert_triangle(int n, float *mx);
/**
 * Apply back substitution to matrix.
 * @param n
 * @param mx
 * @param buffer where is injected the matrix after back substitution
 */
void back_subs(int n, float *mx, float *buffer);

int size = 10;
float value[10][2];

void setup(){
  Serial.begin(9600); // abre a porta serial a 9600 bps;

  value[0][0] = 5.771746026235907;
  value[0][1] = 2756.999505988017;
  value[1][0] = 1.4909464996379098;
  value[1][1] = 331.27119264629675;
  value[2][0] = 9.533623819928094;
  value[2][1] = 6946.331166639915;
  value[3][0] = 8.675744376940758;
  value[3][1] = 5821.543204104686;
  value[4][0] = 2.564082791209792;
  value[4][1] = 705.2624401914835;
  value[5][0] = 5.548095794679393;
  value[5][1] = 2568.557212753365;
  value[6][0] = 6.2094208091037775;
  value[6][1] = 3145.4586196049218;
  value[7][0] = 6.2094208091037775;
  value[7][1] = 3145.4586196049218;
  value[8][0] = 7.145620909711442;
  value[8][1] = 4063.859557631181;
  value[9][0] = 9.383340381276938;
  value[9][1] = 6742.058579154288;
}


void loop() {
    float coef[10];
    find_coefficients(size, &value[0][0], 2, coef);
    float prediction = predict(size, coef, 5.7);

    Serial.print("\n");
    Serial.print("Value is: ");
    Serial.print(prediction);

    Serial.print("           \n");
    Serial.print("           \n");
    delay(1000);
}


// UTILS

float elevate_by(float num, int by){
    float res = 1;
    for (int i = 0; i < by; ++i) {
        res = res * num;
    }
    return res;
}

void print_arr(float *arr, int arr_size){
    printf("{ ");
    for (int i = 0; i < arr_size; ++i) {
        if (i ==0) printf("%.2f", arr[i]);
        else printf(", %.2f", arr[i]);
    }
    printf(" }");
}

void print_matrix(int i, int j, int width, float *arr){
    printf("{ \n");
    for (int k=0; k < i; k++){
        printf("  ");
        printf("{ ");
        for (int u = 0; u < j; ++u) {
            if (u ==0) printf("%.2f", get_from_flattened_matrix(k, u, width, arr));
            else printf(", %.2f", get_from_flattened_matrix(k,u, width, arr));
        }
        printf(" }");
        if (k < i-1) printf(",\n");
    }
    printf("\n");
    printf("}");
}

float get_from_flattened_matrix(int i, int j, int width, float *mx){
    int res = (i * width) + j;
    return mx[res];
}

void set_item_flattened_matrix(int i, int j, int width, float *mx, float value){
    int res = (i * width) + j;
    mx[res] = value;
}

// Utils

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


// Gauss

void gauss_method(int arr_size, float *a, float *b, float *buffer){
    float mx[arr_size][arr_size+1];
    join_mx(arr_size, a, b, &mx[0][0]);
    gauss_method_unique_mx(arr_size, &mx[0][0], buffer);
}

void join_mx(int n, float *mx_a, float *mx_b, float *inject_mx){
    for (int i = 0; i < n; i++) {
        for (int ii = 0; ii < n+1; ii++) {
            if (ii == n)
                set_item_flattened_matrix(i, ii, n+1, inject_mx, get_from_flattened_matrix(i, 0, 1, mx_b));
            else
                set_item_flattened_matrix(i, ii, n+1, inject_mx, get_from_flattened_matrix(i, ii, n, mx_a));
        }
    }
}

void gauss_method_unique_mx(int n, float *mx, float *inject){
    // Apply triangle to matrix.
    convert_triangle(n, mx);
    // Apply back substitution.
    back_subs(n, mx, inject);
}

void convert_triangle(int n, float *mx){
    int i, ii, iii;
    float ratio, temp;
    for( i=0;i<n;i++)
    {
        for(ii=0; ii < n; ii++)
        {
            if(ii > i)
            {
                ratio = get_from_flattened_matrix(ii, i,n+1, mx) / get_from_flattened_matrix(i, i, n+1, mx);
                for(iii=0; iii < n + 1; iii++){
                    float get1 = get_from_flattened_matrix(ii, iii, n+1, mx);
                    float get2 = get_from_flattened_matrix(i, iii, n+1, mx);
                    temp = get1 - ratio * get2;
                    set_item_flattened_matrix(ii, iii, n+1, mx, temp);
                }
            }
        }
    }
}

void back_subs(int n, float *mx, float *buffer){
    int i, ii;
    float sum;
    buffer[n - 1]= get_from_flattened_matrix(n-1, n, n+1, mx) / get_from_flattened_matrix(n-1, n-1, n+1, mx);

    for(i=n-2;i>=0;i--)
    {
        sum=0;
        for(ii= i + 1; ii < n; ii++)
            sum = sum + get_from_flattened_matrix(i, ii, n+1, mx) * buffer[ii];
        buffer[i] = (get_from_flattened_matrix(i, n,n+1, mx) - sum) / get_from_flattened_matrix(i, i, n+1, mx);
    }
}
