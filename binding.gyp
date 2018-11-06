{
  "targets": [
    {
      "target_name": "evilbrisket",
      "include_dirs": [ "<!(node -e \"require('nan')\")" ],
      "sources": [
        "src/LTC2983_support_functions.c",
        "src/evilbrisket_board.c",
        "src/evilbrisket.cc"
      ],
       "libraries": [ "/usr/local/lib/libbcm2835.a" ]
    }
  ]
}