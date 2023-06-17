class Main 
{
    function void main() 
    {
		Array arr;
		String s;
		int i;
		
		arr = Array.new(5);		// 创建一个大小为5的数组
		i = 0;
		while (i < 5)
		{
			s = Input.readLine();
			arr[i] = s.intValue();
			i = i + 1;
		}
		
		Main.bubble_sort(arr, 5);
		
		i = 0;
		while (i < 5)
		{
			Output.printInt(arr[i]);
			i = i + 1;
		}
		Output.println();
		
		return;
	}
	
	/* 冒泡排序 */
	function void bubble_sort(Array arr, int n)
	{
		int i, j, tmp;
		i = n - 1;
		
		while (i > 0 | i == 0)		// 由于还没有加上 >= 运算符, 所以暂时用这个代替
		{
			j = 0;
			while (j < i)
			{
				if (arr[j] > arr[j + 1])
				{
					tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
				j = j + 1;
			}
			i = i - 1;
		}
	
		return;
	}
}