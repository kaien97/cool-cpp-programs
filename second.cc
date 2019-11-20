// This program attempts to minimise the chi^2 value by changing the parameters of a (linear) model // It assumes that there is only 1 minima within the range the user specifies

double chi_squared_value(int data_size, double* x, double* y, double* error, double m, double c) {
  double summed_result = 0;
  for(int i=0; i<data_size; i++)
  {
    double diff = y[i] - (m*x[i]) - c;
    double weighted_diff = diff/(error[i]);
    summed_result += (weighted_diff*weighted_diff);
  }
  return summed_result;
}

int main()
{
  double m_max, m_min, c_max, c_min;
  cout << "This program minimises the chi^2 value of a y = mx + c model by finding the best values for m and c" << endl << endl
       << "Enter a guess for the optimal value of m" << endl << "Max value (of m): ";
  cin >> m_max;
  cout << "Min value (of m): ";
  cin >> m_min;

  cout << endl << "Enter a guess for the optimal value of c" << endl << "Max value (of c): ";
  cin >> c_max;
  cout << "Min value (of c): ";
  cin >> c_min;
  cout << endl;

  int data_size;
  do {
    cout << "It's now time to enter the data. How many data points will there be (minimum 2, maximum 20)? ";
    cin >> data_size;
  } while( (data_size < 2) || (data_size > 20));

  // Enter data
  double x[data_size], y[data_size], error[data_size];
  cout << endl << "Enter data in the format, [x-value] (space) [y-value] (space) [error in y]" << endl;
  for(int i=0; i<data_size; i++)
  {
    cout << "Data point " << i+1 << ": ";
    cin >> x[i] >> y[i] >> error[i];
  }

  // finding optimal value for m
  bool found = false;
  int j = 0;
  double m, m_min_chi, m_max_chi, m_test_one, m_test_two;
  double c_temp = (c_min + c_max)/2;
  while(!found && j < 10000)
  {
    if (m_min == m_max) {
      m = m_min;
      found == true;
    } else {
      m_min_chi = chi_squared_value(data_size, x, y, error, m_min, c_temp);
      m_max_chi = chi_squared_value(data_size, x, y, error, m_max, c_temp);
      m_test_one = chi_squared_value(data_size, x, y, error, m_min + (m_max-m_min)/3, c_temp);
      m_test_two = chi_squared_value(data_size, x, y, error, m_min + ((m_max-m_min)*2)/3, c_temp);

      if (m_min_chi >= m_test_one) {
        m_min = (m_max+m_min)/3;
      } else if (m_test_one <= m_test_two) {
        m_max = (m_max+m_min)/3;
      } else {
        cout << "Enter better guesses for m!" << endl;
        return 0;
      }

      if (m_max_chi >= m_test_two) {
        m_max = ((m_max+m_min)*2)/3;
      } else if (m_test_one >= m_test_two) {
        m_min = ((m_max+m_min)*2)/3;
      } else {
        cout << "Enter better guesses for m!" << endl;
        return 0;
      }

      j++;
      if (j == 1000) {
        m = (m_max + m_min)/2;
      }
    }
  }

  // finding optimal value for c
  found = false;
  j = 0;
  double c, c_min_chi, c_max_chi, c_test_one, c_test_two;
  while(!found && j < 10000)
  {
    if (c_min == c_max) {
      c = c_min;
      found == true;
    } else {
      c_min_chi = chi_squared_value(data_size, x, y, error, m, c_min);
      c_max_chi = chi_squared_value(data_size, x, y, error, m, c_max);
      c_test_one = chi_squared_value(data_size, x, y, error, m, c_min + (c_max-c_min)/3);
      c_test_two = chi_squared_value(data_size, x, y, error, m, c_min + ((c_max-c_min)*2)/3);

      if (c_min_chi >= c_test_one) {
        c_min = (c_max+c_min)/3;
      } else if (c_test_one <= c_test_two) {
        c_max = (c_max+c_min)/3;
      } else {
        cout << "Enter better guesses for c!" << endl;
        return 0;
      }

      if (c_max_chi >= c_test_two) {
        c_max = ((c_max+c_min)*2)/3;
      } else if (c_test_one >= c_test_two) {
        c_min = ((c_max+c_min)*2)/3;
      } else {
        cout << "Enter better guesses for c!" << endl;
        return 0;
      }

      j++;
      if (j == 1000) {
        c = (c_max + c_min)/2;
      }
    }
  }

  cout << "The best guess for m is " << m << endl;
  cout << "The best guess for c is " << c << endl;
  cout << "The chi-squared value is " << chi_squared_value(data_size, x, y, error, m, c) << endl;

  return 0;
}
