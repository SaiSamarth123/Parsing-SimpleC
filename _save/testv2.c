//
// SimpleC 2.0 test program
//
void main()
{
  int x;     // define x:
  cin >> x;  // input a value from the keyboard:

  int y;     // more variables:
  int z;

  y = 3 * 3;  // some computation:
  z = x - y;

  cout << "x: " << x << endl;
  cout << "y: " << y << endl;

  if (z < 0)  // decisions, decisions...
  {
     cout << "z is negative (" << z << ")" << endl;
  }
  else
  {
     cout << "z: " << z << endl;
  }
}
