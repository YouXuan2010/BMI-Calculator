#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate BMI
float calculateBMI(float weight, float height) {
  return weight / (height * height);
}

// Function to classify BMI and provide recommendations for Asians
void classifyAsianBMI(float height, float bmi, char *classification,
                      float *recommendation) {
  if (bmi < 18.5) {
    strcpy(classification, "Low");
    *recommendation =
        (18.5 - bmi) *
        (height *
         height); // No weight change recommended for underweight Asians
  } else if (bmi < 23.0) {
    strcpy(classification, "Normal");
    *recommendation =
        0.0; // No weight change recommended for Asians with normal BMI
  } else if (bmi < 27.5) {
    strcpy(classification, "Overweight");
    *recommendation =
        (23.0 - bmi) * (height * height); // Calculate recommended weight
                                          // reduction to normal BMI for Asians
  } else {
    strcpy(classification, "Obese");
    *recommendation =
        (23.0 - bmi) * (height * height); // Calculate recommended weight
                                          // reduction to normal BMI for Asians
  }
}

// Function to classify BMI and provide recommendations for non-Asians
void classifyNonAsianBMI(float height, float bmi, char *classification,
                         float *recommendation) {
  if (bmi < 18.5) {
    strcpy(classification, "Low");
    *recommendation =
        (18.5 - bmi) *
        (height *
         height); // No weight change recommended for underweight non-Asians
  } else if (bmi < 24.9) {
    strcpy(classification, "Normal");
    *recommendation =
        0.0; // No weight change recommended for non-Asians with normal BMI
  } else if (bmi < 29.9) {
    strcpy(classification, "Overweight");
    *recommendation =
        (24.9 - bmi) *
        (height * height); // Calculate recommended weight reduction to normal
                           // BMI for non-Asians
  } else {
    strcpy(classification, "Obese");
    *recommendation =
        (24.9 - bmi) *
        (height * height); // Calculate recommended weight reduction to normal
                           // BMI for non-Asians
  }
}

// Function to validate float input
float getValidFloatInput(const char *prompt, const char *type) {
  char inputStr[100]; // Buffer to store user input as string
  float value;
  int input;
  char *endPtr;

  do {
    printf("=========================================================\n");
    printf("%s", prompt);
    fgets(inputStr, sizeof(inputStr), stdin); // Read input as string

    // Remove newline character from input
    if (inputStr[strlen(inputStr) - 1] == '\n')
      inputStr[strlen(inputStr) - 1] = '\0';

    // Check if the input contains only numeric characters and at most one
    // decimal point
    int validInput = 1;
    int decimalPointCount = 0;
    for (int i = 0; i < strlen(inputStr); i++) {
      if (!isdigit(inputStr[i])) {
        if (inputStr[i] == '.') {
          decimalPointCount++;
          if (decimalPointCount > 1) {
            validInput = 0;
            break;
          }
        } else {
          validInput = 0;
          break;
        }
      }
    }

    if (!validInput) {
      printf("Invalid input. Please enter a valid numeric input.\n");
      continue;
    }

    // Convert the input string to float
    value = strtof(inputStr, &endPtr);
    if (endPtr == inputStr) {
      printf("No input detected. Please re-enter.\n");
      continue;
    }

    // Check the type of input and validate the range
    switch (*type) {
    case 'h': // Height
      if (value <= 1.2 || value > 3) {
        printf("Height out of range. Please enter a valid height in METRES.\n");
        continue;
      }
      break;
    case 'w': // Weight
      if (value <= 20 || value > 500) {
        printf(
            "Weight out of range. Please enter a valid weight in KILOGRAMS.\n");
        continue;
      }
      break;
    default:
      printf("Invalid input type.\n");
      continue;
    }
    break;
  } while (1);
  return value;
}

int getValidCharInput(const char *prompt) {
  char input[100]; // Buffer to store user input
  int isValidInput = 0;
  int length;

  do {
    printf("=========================================================\n");
    printf("%s", prompt);
    fgets(input, sizeof(input), stdin); // Read input as string

    // Remove newline character from input
    length = strlen(input);
    if (input[length - 1] == '\n')
      input[length - 1] = '\0';

    // Check if the input length is valid
    if (strlen(input) != 1) {
      printf("Please enter only ONE character.\n");
      continue;
    }

    // Convert input to uppercase
    input[0] = toupper(input[0]);

    // Check if the input is valid (Y or N)
    if (input[0] == 'Y' || input[0] == 'N') {
      isValidInput = 1;
    } else {
      printf("Please enter either 'Y' or 'N'.\n");
    }

  } while (!isValidInput);

  // Return 1 for 'Y' and 0 for 'N'
  return (input[0] == 'Y') ? 1 : 0;
}

int main() {
  float weight, height, bmi, recommendation;
  char classification[20];
  int isAsian, weight_input, height_input;

  // Get valid weight input
  weight = getValidFloatInput("Enter your weight in kg: ", "w");

  // Get valid height input
  height = getValidFloatInput("Enter your height in meters: ", "h");

  // Input whether the user is Asian or not
  isAsian = getValidCharInput("Are you Asian? (Y for Yes, N for No): ");

  // Calculate BMI
  bmi = calculateBMI(weight, height);

  // Classify BMI and provide recommendations based on Asian status
  if (isAsian) {
    classifyAsianBMI(height, bmi, classification, &recommendation);
  } else {
    classifyNonAsianBMI(height, bmi, classification, &recommendation);
  }

  // Output results in a table format
  printf("\nBMI Report:\n");
  printf("+---------------------+-----------------+\n");
  printf("|    Parameter        |    Value        |\n");
  printf("+---------------------+-----------------+\n");
  printf("|    Weight           |    %-10.2f\t|\n", weight);
  printf("|    Height           |    %-10.2f\t|\n", height);
  printf("|    BMI              |    %-10.2f\t|\n", bmi);
  printf("|    Classification   |    %-10s\t|\n", classification);
  printf("|    Recommendation   |    %-10.2f\t|\n", recommendation);
  printf("+---------------------+-----------------+\n");

  return 0;
}