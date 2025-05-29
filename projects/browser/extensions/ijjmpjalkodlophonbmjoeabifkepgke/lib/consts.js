// export const HTTP_SERVER_URL = "http://192.168.0.25:10888/api/v1/user/gen_cookie";
// export const HTTP_SERVER_ERROR_URL = "http://192.168.0.25:10888/api/v1/user/error";
// export const HTTP_SERVER_URL =
//   "http://192.168.0.100:10888/api/v1/user/gen_cookie";
// export const HTTP_SERVER_ERROR_URL =
//   "http://192.168.0.100:10888/api/v1/user/error";
export const HTTP_SERVER_URL = "https://search.yunlogin.com/api/v1/user/gen_cookie";
export const HTTP_SERVER_ERROR_URL = "https://search.yunlogin.com/api/v1/user/error";

export const EXCLUDE_URL_PREFIXES = [
  "chrome://",
  "https://whoer.net",
  "https://hao.360.com",
];

export const SEARCH_RANDOM_KEYWORDS = [
  "hello",
  "world",
  "test",
  "ai",
  "cookie",
  "search",
  "random",
  "bing",
  "baidu",
  "google",
  "extension",
  "browser",
  "javascript",
  "chrome",
  "firefox",
  "safari",
  "edge",
  "web",
  "api",
  "network",
  "data",
  "json",
  "http",
  "https",
  "url",
  "keyword",
  "query",
  "content",
  "script",
  "function",
  "variable",
  "object",
  "array",
  "string",
  "number",
  "boolean",
  "null",
  "undefined",
];

export const TARGETS = [
  {
    url: "https://www.google.com/search?q=",
    domain: ".google.com",
    refreshInterval: 10 * 1000,
  },
];

export const TARGET_DOMAINS = [".google.com"];

export const PROXY_BYPASS_LIST = [
  "192.168.0.25",
  "192.168.0.100",
  "127.0.0.1",
  "localhost",
];

export const PROXY_AUTH_CONFIGS = [
  // 美国-洛杉矶-双NTT
  {
    host: "204.141.248.124",
    port: 5206,
    username: "tgjnt2uw3xdq",
    password: "fnkrr2efndta",
  },
  {
    host: "204.141.248.115",
    port: 5206,
    username: "pgjnt2uw3j5m",
    password: "peqsauex4rtm",
  },
  {
    host: "204.141.248.122",
    port: 5206,
    username: "hgjnt2uw39qz",
    password: "ganhvs4r7u6u",
  },
  {
    host: "204.141.248.155",
    port: 5206,
    username: "ygjnt2uw37v7",
    password: "cqwrasqqviex",
  },
  {
    host: "204.141.248.95",
    port: 5206,
    username: "kgjnt2uw9xg3",
    password: "jfeydztqhg7x",
  },
  {
    host: "204.141.248.180",
    port: 5206,
    username: "cgjnt8gbjhiz",
    password: "ajwp2mzcmg2d",
  },
  {
    host: "204.141.248.111",
    port: 5206,
    username: "bgjnjbidxctr",
    password: "rbxi5qeuyhwn",
  },
  {
    host: "204.141.248.119",
    port: 5206,
    username: "wgjnmwhqfzu7",
    password: "kxgwzahngtu2",
  },
  {
    host: "204.141.248.245",
    port: 5206,
    username: "fgjnmjecyth2",
    password: "hyaxxgjnyt7z",
  },
  {
    host: "204.141.248.99",
    port: 5206,
    username: "jgjnmjecy89j",
    password: "gxnu2gxghtcu",
  },

  {
    host: "140.174.161.102",
    port: 5206,
    username: "wgjkxapkh6mc",
    password: "rizz37j6lpn0",
  },
  {
    host: "140.174.161.58",
    port: 5206,
    username: "igjkxapkhixs",
    password: "kjyp2cqkki46",
  },
  {
    host: "140.174.161.12",
    port: 5206,
    username: "wgjn5rtv6krr",
    password: "wcxnmzq2p88q",
  },
  {
    host: "140.174.161.30",
    port: 5206,
    username: "ggjta7rfhknp",
    password: "crfr6g2cmpej",
  },
  {
    host: "140.174.161.40",
    port: 5206,
    username: "fgjta7rfh5rg",
    password: "emgxpnqv82nn",
  },
  {
    host: "140.174.161.235",
    port: 5206,
    username: "fgjta7rfia7p",
    password: "naunert7fdcu",
  },
  {
    host: "140.174.161.195",
    port: 5206,
    username: "ugjta7rfunfp",
    password: "kkch27pud4b4",
  },
  {
    host: "140.174.161.178",
    port: 5206,
    username: "jgjta7rfuuw9",
    password: "yjbdl572ghvp",
  },
  {
    host: "140.174.161.163",
    port: 5206,
    username: "rgjta7rfupt3",
    password: "rrigde9osq0e",
  },
  {
    host: "140.174.161.137",
    port: 5206,
    username: "tgjta7rfijmg",
    password: "dzucoumctuv1",
  },

  // 美国-达拉斯
  {
    host: "107.158.131.166",
    port: 34471,
    username: "1AeRYA107158131166A34471",
    password: "Wqire1Cr8IRr",
  },
  {
    host: "107.158.131.233",
    port: 30892,
    username: "1AeRZA107158131233A30892",
    password: "PlOyuD201DSH",
  },
  {
    host: "107.158.131.238",
    port: 43040,
    username: "1AeRaA107158131238A43040",
    password: "11Zg5cjxyC3P",
  },
  {
    host: "107.158.131.82",
    port: 47757,
    username: "1AeRbA10715813182A47757",
    password: "PTvGa473YZC5",
  },
  {
    host: "107.158.131.228",
    port: 47641,
    username: "1AeRcA107158131228A47641",
    password: "LSy3oMDqOPq3",
  },
  {
    host: "107.158.131.105",
    port: 47808,
    username: "1AeRdA107158131105A47808",
    password: "wqi72XT56FyW",
  },
  {
    host: "107.158.131.58",
    port: 41483,
    username: "1AeReA10715813158A41483",
    password: "gDjejOHFkNxF",
  },
  {
    host: "107.158.131.144",
    port: 32917,
    username: "1AeRfA107158131144A32917",
    password: "U3PvjvxKn2f2",
  },
  {
    host: "107.158.131.92",
    port: 40186,
    username: "1AeRgA10715813192A40186",
    password: "yBVNjeXUQIyD",
  },
  {
    host: "107.158.131.230",
    port: 42583,
    username: "1AeRhA107158131230A42583",
    password: "ZoS8QVpm9wwP",
  },
  {
    host: "107.158.131.155",
    port: 48211,
    username: "1AeRiA107158131155A48211",
    password: "FmD3IHmjzGc5",
  },

  // 美国-休斯顿
  {
    host: "38.248.230.224",
    port: 44902,
    username: "1AUnqA38248230224A44902",
    password: "rOkBMd3nTs3X",
  },
  {
    host: "38.248.230.34",
    port: 39043,
    username: "1AUnpA3824823034A39043",
    password: "THweh6wf8LjI",
  },
  {
    host: "38.248.230.79",
    port: 39923,
    username: "1AUnnA3824823079A39923",
    password: "SuQy7X1MSSaQ",
  },
  {
    host: "38.248.230.236",
    port: 46053,
    username: "1AUnxA38248230236A46053",
    password: "QsAH0ComwzTs",
  },
  {
    host: "38.248.230.188",
    port: 49648,
    username: "1AV2HA38248230188A49648",
    password: "hpCiuWw3pZFk",
  },
  {
    host: "38.248.230.223",
    port: 44050,
    username: "1AV2vA38248230223A44050",
    password: "izOWPa0YqFgK",
  },
  {
    host: "38.248.230.69",
    port: 34864,
    username: "1AaigA3824823069A34864",
    password: "xn2EqfdCjMh8",
  },
  {
    host: "38.248.230.9",
    port: 32695,
    username: "1AV3SA382482309A32695",
    password: "UbBgbyq6iOyM",
  },
  {
    host: "38.248.230.158",
    port: 43425,
    username: "1AV7jA38248230158A43425",
    password: "v4TDf0ig2iap",
  },
  {
    host: "38.248.230.163",
    port: 36499,
    username: "1AV7kA38248230163A36499",
    password: "M6aFyUo6z7BY",
  },

  // 美国-维吉尼亚
  {
    host: "50.3.97.53",
    port: 33426,
    username: "1AfH1A5039753A33426",
    password: "CEMvuzpawptB",
  },
  {
    host: "50.3.97.159",
    port: 35765,
    username: "1AfH3A50397159A35765",
    password: "bTyUDs3ZICGT",
  },
  {
    host: "50.3.97.55",
    port: 43398,
    username: "1AfH4A5039755A43398",
    password: "D6T42aCr7m2O",
  },
  {
    host: "50.3.97.229",
    port: 31035,
    username: "1AfH5A50397229A31035",
    password: "uFXkYRKaUn4y",
  },
  {
    host: "50.3.97.43",
    port: 43915,
    username: "1AfH7A5039743A43915",
    password: "nIch3RiuGTyO",
  },
  {
    host: "50.3.97.244",
    port: 47208,
    username: "1AfH8A50397244A47208",
    password: "68TNew5OnoJf",
  },
  {
    host: "50.3.97.150",
    port: 30342,
    username: "1AfH9A50397150A30342",
    password: "tuh0g4zt96hq",
  },
  {
    host: "50.3.97.96",
    port: 41187,
    username: "1AfHMA5039796A41187",
    password: "RzfE18fXNxte",
  },
  {
    host: "50.3.97.50",
    port: 47845,
    username: "1AfHRA5039750A47845",
    password: "2i4iN1xny22r",
  },

  // 英国-伦敦-双ISP
  {
    host: "165.65.161.152",
    port: 5206,
    username: "ngjm4hiek99r",
    password: "uhmdwrfwzc4m",
  },
  {
    host: "165.65.161.221",
    port: 5206,
    username: "cgjm4hiek7ph",
    password: "qjeuxcgzdrq5",
  },
  {
    host: "165.65.161.44",
    port: 5206,
    username: "xgjm4hiema73",
    password: "zdifadbawvsp",
  },
  {
    host: "165.65.161.132",
    port: 5206,
    username: "sgjm4hieme4q",
    password: "tyke6u7qvbiz",
  },
  {
    host: "165.65.161.65",
    port: 5206,
    username: "bgjm4hiemu9r",
    password: "agcmrfhg5qsc",
  },
  {
    host: "165.65.161.45",
    port: 5206,
    username: "fgjm4hiemy5k",
    password: "ccbb3b46bpyt",
  },
  {
    host: "165.65.161.141",
    port: 5206,
    username: "ygjm4hiemk9h",
    password: "detuaizciy67",
  },
  {
    host: "165.65.161.175",
    port: 5206,
    username: "pgjm4hiemr3d",
    password: "kmsf9g8tha4y",
  },
  {
    host: "165.65.161.71",
    port: 5206,
    username: "sgjm4hiem9qk",
    password: "pswqwg7niybh",
  },
  {
    host: "165.65.161.253",
    port: 5206,
    username: "xgjm4hiem82b",
    password: "btynui3u4ne9",
  },
  {
    host: "165.65.161.131",
    port: 5206,
    username: "kgjm4hiena7m",
    password: "zuuave9ujk35",
  },
  {
    host: "165.65.161.144",
    port: 5206,
    username: "kgjm4hienfed",
    password: "gina2dpdiyr8",
  },

  // 德国-柏林-双ISP
  {
    host: "212.102.228.161",
    port: 5206,
    username: "jgjtbm7ks24r",
    password: "zhxc5qobstif",
  },
  {
    host: "212.102.228.207",
    port: 5206,
    username: "bgjtbm7ksu9n",
    password: "ycqffd7vq3fd",
  },
  {
    host: "212.102.228.254",
    port: 5206,
    username: "fgjtbm7kstqv",
    password: "qeag23btremh",
  },
  {
    host: "212.102.228.248",
    port: 5206,
    username: "agjtbm4i3iqn",
    password: "gemzqtc9s4aj",
  },
  {
    host: "212.102.228.167",
    port: 5206,
    username: "rgjtbm4i3zv7",
    password: "qudnlk31vgro",
  },
  {
    host: "212.102.228.8",
    port: 5206,
    username: "igjtbm4i55uv",
    password: "amer4rvao5tb",
  },
  {
    host: "212.102.228.103",
    port: 5206,
    username: "xgjtbm4i58ey",
    password: "zvpk4509qj2h",
  },
  {
    host: "212.102.228.241",
    port: 5206,
    username: "bgjtbm4i3b8g",
    password: "uiyx5h82j018",
  },
  {
    host: "212.102.228.201",
    port: 5206,
    username: "xgjtbm4i5ku4",
    password: "umredo6659vb",
  },
  {
    host: "212.102.228.151",
    port: 5206,
    username: "egjtb7k78w39",
    password: "veddvm5nb57s",
  },

  // 法国-巴黎-双ISP
  {
    host: "144.56.25.177",
    port: 5206,
    username: "dgjm72tyck43",
    password: "tbekjxd4bm92",
  },
  {
    host: "144.56.25.110",
    port: 5206,
    username: "igjm72tycsn4",
    password: "yrhwfcvt6pd5",
  },
  {
    host: "144.56.25.166",
    port: 5206,
    username: "hgjnpa9weksf",
    password: "njeytqrd9xth",
  },
  {
    host: "144.56.25.30",
    port: 5206,
    username: "rgjnakbzzyns",
    password: "rygd39fc3gxc",
  },
  {
    host: "144.56.25.131",
    port: 5206,
    username: "hgjnakbzzmxf",
    password: "fcyv7jvikryz",
  },
  {
    host: "144.56.25.212",
    port: 5206,
    username: "kgjnakbzz5cd",
    password: "jzvmkhngfhxw",
  },
  {
    host: "144.56.25.165",
    port: 5206,
    username: "ngjnakbzz698",
    password: "ryykmpzwrv5k",
  },
  {
    host: "144.56.25.39",
    port: 5206,
    username: "zgjncvqwz2xm",
    password: "jwcu6px95gqw",
  },
  {
    host: "144.56.25.136",
    port: 5206,
    username: "rgjncvqwtphy",
    password: "dmpmxjddxhvb",
  },
  {
    host: "144.56.25.19",
    port: 5206,
    username: "ngjncvqwtc74",
    password: "aszqp8nxtkc4",
  },
  {
    host: "144.56.25.31",
    port: 5206,
    username: "igjnc3dzig8j",
    password: "hbvviu9sntb7",
  },

  // 日本-千叶-双ISP
  {
    host: "160.22.229.94",
    port: 5206,
    username: "ngjmsmkjxe4x",
    password: "kkbkga5cjuei",
  },
  {
    host: "160.22.229.24",
    port: 5206,
    username: "qgjmsmkjxvjr",
    password: "ysqbcpnuqecq",
  },
  {
    host: "160.22.229.140",
    port: 5206,
    username: "zgjmsmkjxtej",
    password: "qyuwmga4pcq8",
  },
  {
    host: "160.22.229.46",
    port: 5206,
    username: "wgjmsmkjxqdr",
    password: "scggurfifnm5",
  },
  {
    host: "160.22.229.145",
    port: 5206,
    username: "wgjmsmkjx388",
    password: "rpynfp85qaqm",
  },
  {
    host: "160.22.229.32",
    port: 5206,
    username: "agjmsmmxbxuh",
    password: "hjez474wpm2z",
  },
  {
    host: "160.22.229.47",
    port: 5206,
    username: "pgjmsmmxbka7",
    password: "iregvp2wa9xf",
  },
  {
    host: "160.22.229.215",
    port: 5206,
    username: "jgjmsmmxbr2t",
    password: "zcnzsbkk4h8n",
  },
  {
    host: "160.22.229.37",
    port: 5206,
    username: "fgjmsmmxb2q4",
    password: "eqmfds76deqe",
  },
  {
    host: "160.22.229.184",
    port: 5206,
    username: "pgjmsmmxcptc",
    password: "xert4v7wpamk",
  },
  {
    host: "160.22.229.192",
    port: 5206,
    username: "sgjmsmmxcdc6",
    password: "vjergw8k6ijx",
  },

  // 中国-香港
  {
    host: "38.182.98.247",
    port: 46117,
    username: "1AZFFA3818298247A46117",
    password: "fFHGVdvBwMat",
  },
  {
    host: "38.182.98.151",
    port: 48056,
    username: "1AZFGA3818298151A48056",
    password: "hmnb4EzutGSR",
  },
  {
    host: "38.182.98.183",
    port: 48154,
    username: "1AZFJA3818298183A48154",
    password: "u4YedMsoSLQO",
  },
  {
    host: "38.182.98.6",
    port: 36580,
    username: "1AZFKA38182986A36580",
    password: "kKM6ispACPBM",
  },
  {
    host: "38.182.98.18",
    port: 49295,
    username: "1AZFLA381829818A49295",
    password: "PodTmJqDjncY",
  },
  {
    host: "38.182.98.195",
    port: 46212,
    username: "1AZFNA3818298195A46212",
    password: "fd9OJxR3wGyc",
  },
  {
    host: "38.182.98.176",
    port: 40103,
    username: "1AZFPA3818298176A40103",
    password: "7BrUZT9s1Xbr",
  },
  {
    host: "38.182.98.149",
    port: 36333,
    username: "1AZFTA3818298149A36333",
    password: "yQDOzRelXX3X",
  },
  {
    host: "38.182.98.48",
    port: 39549,
    username: "1AZFWA381829848A39549",
    password: "DXopHWEoSWXt",
  },
  {
    host: "38.182.98.4",
    port: 45425,
    username: "1AZG5A38182984A45425",
    password: "wXvdxHmw1ADp",
  },
];
