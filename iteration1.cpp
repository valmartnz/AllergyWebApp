#include <iostream>
#include <memory>

#include <allheaders.h> // leptonica main header for image io
#include <tesseract/baseapi.h> // tesseract header to be able to call tessaract

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>

int main(int argc, char *argv[]) {

  if(argc == 1) { return 1; }

  // cv::Mat m;

  char userOption;
  std::string userAllergy[15];
  std::string userPurchases[15];
  int n = 0, c = 0;

  std::cout << "Welcome! Please input number choice.\n";
  do{
    std::cout << "Menu: \n"
  		           "1. Input Food Allergy \n"
  		           "2. View Food Allergies\n"
  		           "3. Scan Food Ingredients\n"
                 "4. Input Previous Food Purchases\n"
                 "5. View Previous Food Purchases\n"
                 "6. Recommended Food Purchases\n"
                 "7. Exit\n\n";

    std::cin >> userOption;

    switch (userOption) {
      case '1':
        std::cout << "\nInput known allergy.\n";
        std::cin >> userAllergy[n++];
        std::cout << "\n\n";
        break;
      case '2':
        std::cout << "\nKnown Food Allergies:\n";
        for(int i = 0; i < n; i++) {
          std::cout << userAllergy[i] << std::endl;
        }
        std::cout << "\n\n";
        break;
      case '3':
        std::cout << "\nUpload image to scan ingredients.\n";
        tesseract::TessBaseAPI tess;

        if(tess.Init("./tessdata", "eng")) {
          std::cout << "OCRTesseract: Could not initialize tesseract." << std::endl;
          return 1;
        }

        // setup
        tess.SetPageSegMode(tesseract::PageSegMode::PSM_AUTO);
        tess.SetVariable("save_best_choices", "T");

        // read image
        auto pixs = pixRead(argv[1]);
        if(!pixs) {
          std::cout << "Cannot open input file: " << argv[1] << std::endl;
          return 1;
        }

        // recognize
        tess.SetImage(pixs);
        tess.Recognize(0);

        // get result and delete[] returned char* string
        std::cout << std::unique_ptr<char[]>(tess.GetUTF8Text()).get() << std::endl;

        // cleanup
        tess.Clear();
        pixDestroy(&pixs);
        std::cout << "\n\n";
        break;
      case '4':
        std::cout << "\nInput a previous food purchase:\n";
        std::cin >> userPurchases[c++];
        std::cout << "\n\n";
        break;
      case '5':
        std::cout << "\nPrevious Food Purchases:\n";
        for(int i = 0; i < c; i++) {
          std::cout << userPurchases[i] << std::endl;
        }
        std::cout << "\n\n";
        break;
      case '6':
        std::cout << "\nRecommended Food Purchases:\n";
        for(int i = 0; i < c; i++) {
          std::cout << userPurchases[i] << std::endl;
        }
        std::cout << "\n\n";
        break;
      case '7':
        std::cout << "\nThank you!\n";
        break;
      default:
        std::cout << "\nInvalid option. Try again.\n\n";
   }
  } while(userOption != '7');

  return 0;
}
