// pch.h: это предварительно скомпилированный заголовочный файл.
// Перечисленные ниже файлы компилируются только один раз, что ускоряет последующие сборки.
// Это также влияет на работу IntelliSense, включая многие функции просмотра и завершения кода.
// Однако изменение любого из приведенных здесь файлов между операциями сборки приведет к повторной компиляции всех(!) этих файлов.
// Не добавляйте сюда файлы, которые планируете часто изменять, так как в этом случае выигрыша в производительности не будет.

#ifndef PCH_H
#define PCH_H

// Добавьте сюда заголовочные файлы для предварительной компиляции
#include <cstdint>
#include <ios>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include "InputStreams/IInputStream.h"
#include "InputStreams/FileInputStream.h"
#include "OutputStreams/IOutputStream.h"
#include "OutputStreams/FileOutputStream.h"
#include "InputStreams/MemoryInputStream.h"
#include "OutputStreams/MemoryOutputStream.h"

#include "InputStreams/Decorators/DecryptInputStream.h"
#include "InputStreams/Decorators/SubstitutionCipherDecryptInputStream.h"

#include "OutputStreams/Decorators/EncryptOutputStream.h"
#include "OutputStreams/Decorators/SubstitutionCipherEncryptOutputStream.h"

#include "InputStreams/Decorators/DecompressInputStream.h"
#include "InputStreams/Decorators/RLEDecompressInputStream.h"

#include "OutputStreams/Decorators/CompressOutputStream.h"
#include "OutputStreams/Decorators/RLECompressOutputStream.h"

#endif //PCH_H
