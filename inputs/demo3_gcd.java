class Main
{
	function void demo3_gcd()
	{
		int a, b, c;
		String s;
		
		s = Input.readLine();
		a = s.intValue();
		
		s = Input.readLine();
		b = s.intValue();
		
		c = Main.gcd(a, b);   
		
		Output.printInt(c);
		Output.println();
		
		return;
	}
	
	// 求最大公约数
	function int gcd(int a, int b)
	{
		if (b == 0)
		{
			return a;
		}
		else
		{
			return Main.gcd(b, a - a / b * b);
		}
	}
	
}