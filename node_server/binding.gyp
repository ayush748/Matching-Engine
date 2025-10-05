{
  "targets": [
    {
      "target_name": "binding",
      "sources": [
        "binding.cpp",
        "../src/matching_engine.cpp",
        "../src/order_book.cpp",
        "../src/order.cpp",
        "../src/trade.cpp"
      ],
      "include_dirs": [
        "<!(node -p \"require('node-addon-api').include\")",
        "node_modules/node-addon-api",
        "../include"
      ],
      "defines": ["NAPI_CPP_EXCEPTIONS"],
      "cflags_cc!": ["-fno-exceptions"]
    }
  ]
}

