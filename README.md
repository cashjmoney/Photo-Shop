
## C++ Source Code

### `main.cpp`

This is the main driver code for the project. It accepts command-line arguments to perform various image processing tasks on `.tga` files.

### Key Components

- **Global Variables**:
  - `Image t_image`: Holds the processed image.
  - `Image input_1, input_2, input_3`: Used for reading and processing input images.

- **Helper Functions**:
  - `bool tgachecker(string& tga)`: Validates if the provided filename ends with `.tga`.
  - `string conversion(char*& command)`: Converts a `char*` command-line argument to a `string`.

- **Main Functionality**:
  - The program begins by checking for basic errors, such as missing arguments or invalid file formats.
  - Based on the provided command-line arguments, it performs different image processing methods such as `multiply`, `subtract`, `flip`, `overlay`, `screen`, `onlyred`, `onlygreen`, `onlyblue`, `addgreen`, `addred`, `addblue`, `combine`, `scalered`, `scaleblue`, and `scalegreen`.

### Example Methods

1. **Multiply**:
   - Combines two images by multiplying their color channels.
   - ```cpp
     t_image = t_image.multiply(t_image, input_2);
     ```

2. **Subtract**:
   - Subtracts the color channels of the second image from the first.
   - ```cpp
     t_image = t_image.subtract(t_image, input_2);
     ```

3. **Flip**:
   - Flips the image upside down.
   - ```cpp
     t_image = t_image.upsidedown(t_image);
     ```

4. **Color Channel Scaling**:
   - Adjusts the intensity of the red, green, or blue channels.
   - ```cpp
     t_image = t_image.scale_red(t_image, increase);
     ```

## Makefile

### Build Instructions

The `Makefile` automates the build and run processes for the project.

- **Build**:
  ```makefile
  build:
	g++ -std=c++11 -o project2.out src/*.cpp

