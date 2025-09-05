import 'dart:ffi';
import 'dart:typed_data';
import 'package:ffi/ffi.dart';

typedef GetDominantColorFromMemoryC = Uint32 Function(
  Pointer<Uint8>,
  Int32,
  Int32,
);

typedef GetDominantColorFromMemoryDart = int Function(
  Pointer<Uint8>,
  int,
  int,
);

typedef GetDominantColorFromFileC = Uint32 Function(Pointer<Utf8>);
typedef GetDominantColorFromFileDart = int Function(Pointer<Utf8>);

class DominantColor {
  late final DynamicLibrary _lib;
  late final GetDominantColorFromMemoryDart _fromMemory;

  DominantColor() {
    _lib = DynamicLibrary.open("libc_bindings.so");
    _fromMemory = _lib.lookupFunction<GetDominantColorFromMemoryC,
        GetDominantColorFromMemoryDart>(
      "GetDominantColor",
    );
  }

  int getDominantColor(Uint8List rgbData, int width, int height) {
    final ptr = malloc<Uint8>(rgbData.length);
    final nativeBytes = ptr.asTypedList(rgbData.length);
    nativeBytes.setAll(0, rgbData);

    final result = _fromMemory(ptr, width, height);

    malloc.free(ptr);
    return result;
  }
}
