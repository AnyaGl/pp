#include <iostream>
#include "Bitmap.h"
#include <algorithm>

void Blur(Bitmap* bmp, int radius)
{
	float rs = ceil(radius * 2.57);
	std::cout << bmp->GetHeight() << std::endl;
	for (int i = 0; i < bmp->GetHeight(); ++i)
	{
		for (int j = 0; j < bmp->GetWidth(); ++j)
		{
			double r = 0, g = 0, b = 0;
			double count = 0;

			for (int iy = i - rs; iy < i + rs + 1; ++iy)
			{
				for (int ix = j - rs; ix < j + rs + 1; ++ix)
				{
					auto x = min(static_cast<int>(bmp->GetWidth()) - 1, max(0, ix));
					auto y = min(static_cast<int>(bmp->GetHeight()) - 1, max(0, iy));

					auto dsq = ((ix - j) * (ix - j)) + ((iy - i) * (iy - i));
					auto wght = std::exp(-dsq / (2.0 * radius * radius)) / (3.14 * 2.0 * radius * radius);

					rgb32* pixel = bmp->GetPixel(x, y);

					r += pixel->r * wght;
					g += pixel->g * wght;
					b += pixel->b * wght;
					count += wght;
				}
			}

			rgb32* pixel = bmp->GetPixel(j, i);
			pixel->r = std::round(r / count);
			pixel->g = std::round(g / count);
			pixel->b = std::round(b / count);
		}
		std::cout << i << std::endl;
	}
}

int main()
{
	auto fileIn = "fox.bmp";
	auto fileOut = "image_out.bmp";

	Bitmap bmp(fileIn);
	Blur(&bmp, 5);
	bmp.Save(fileOut);
	return 0;
}
