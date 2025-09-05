import 'dart:developer';
import 'package:dominant_color_with_cpp/dominant_color_ffi.dart';
import 'package:flutter/material.dart';
import 'package:http/http.dart' as http;
import 'package:image/image.dart' as img;

void main() {
  runApp(const MainApp());
}

const int alphaChannel = 0xFF000000;

class MainApp extends StatefulWidget {
  const MainApp({super.key});

  @override
  State<MainApp> createState() => _MainAppState();
}

class _MainAppState extends State<MainApp> {
  final dominantColor = DominantColor();
  int? colorCode;
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      home: Scaffold(
        floatingActionButton: FloatingActionButton(
          child: const Text("Touch"),
          onPressed: () async {
            var result = await http.get(Uri.parse(
                "https://images.hdqwalls.com/download/minimal-landscape-sunrise-4k-jy-1920x1080.jpg"));

            img.Image decoded = img.decodeImage(result.bodyBytes)!;
            colorCode = dominantColor.getDominantColor(
              decoded.getBytes(),
              decoded.width,
              decoded.height,
            );

            setState(() {});
            log("colorCode = $colorCode");
          },
        ),
        body: Center(
          child: Container(
            height: 300,
            width: 300,
            color: colorCode == null
                ? Colors.amber
                : Color(colorCode! | alphaChannel),
          ),
        ),
      ),
    );
  }
}
