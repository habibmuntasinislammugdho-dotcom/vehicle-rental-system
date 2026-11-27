# Vehicle Rental System (C, CSV)

## চালানোর নিয়ম (VS Code, Windows)

1. Zip **Extract All** করুন। VS Code-এ **File → Open Folder** দিয়ে `vehicle-rental-system` ফোল্ডারটি খুলুন (শুধু একটি ফাইল নয়)। যে ফোল্ডারে `src`, `data`, `run.bat` দেখা যায় সেটিই সঠিক ফোল্ডার।
2. Terminal খুলে (Terminal → New Terminal) লিখুন: `.\run.bat`
3. অথবা **Ctrl + Shift + B** চাপুন।

**▶ (Run Code / Run C File) বাটন ব্যবহার করবেন না।** এটি সাধারণত একটি ফাইল compile করে, তাই `undefined reference` error আসে।

Admin login: username `admin`, password `1234`

### সমস্যা হলে

| সমস্যা | সমাধান |
|---|---|
| `gcc is not recognized` | MinGW-w64 (GCC) install করে এর `bin` ফোল্ডার PATH-এ যোগ করুন, তারপর VS Code বন্ধ করে আবার খুলুন। `gcc --version` দিয়ে যাচাই করুন। |
| `vrs.exe: Permission denied` | আগের প্রোগ্রাম চলছে। সেটি বন্ধ করুন (menu থেকে 0, বা Ctrl + C)। |
| `could not save` / `cannot save bill` | CSV ফাইল Excel-এ খোলা থাকলে বন্ধ করুন। |

CSV ফাইল Excel-এ edit করে save করবেন না। Excel তারিখ ও ফোন নম্বরের (শুরুর 0) format বদলে দিতে পারে। দেখার জন্য VS Code ব্যবহার করুন।

## মডিউল ভাগ

| মডিউল | ফাইল | কাজ |
|---|---|---|
| 1. Vehicle Management | `vehicle.c`, `vehicle.h` | গাড়ি add, view, update, remove, status |
| 2. Customer Booking | `booking.c`, `booking.h` | browse, estimate, booking, cancel |
| 3. Rental & Return | `rental.c`, `rental.h` | ongoing rental, return, late দিন |
| 4. Billing & Costing | `billing.c`, `billing.h` | খরচ হিসাব, bill, income report |
| Common (team) | `main.c`, `utils.c`, `utils.h`, `common.h` | menu, login, input validation, CSV helper |

## Billing-এর নিয়ম

নিচের রেট ও চার্জ নমুনা হিসেবে ধরা। `billing.c` থেকে বদলানো যায়।

- দৈনিক ভাড়া: Car 3000, SUV 4500, Microbus 5000, Bike 800 টাকা
- Driver: 800/দিন (late দিনেও), Insurance: 300/দিন (শুধু booked দিন)
- ৭ দিন বা বেশি হলে rental cost-এ 10% discount
- Late fee: প্রতি late দিনে দৈনিক ভাড়ার 150%
- VAT: 5%
- আগে ফেরত দিলেও booked দিনের পুরো ভাড়া
- Late দিন = (return date − start date) − booked দিন

উদাহরণ: Car, ৩ দিন, driver ও insurance সহ, ২ দিন late, damage 500:
ভাড়া 9000 + driver 4000 (৫ দিন) + insurance 900 + late 9000 + damage 500 = 23400; VAT 1170; **মোট 24570**

## কোন C concept কোথায়

| Concept | উদাহরণ |
|---|---|
| File handling | `fopen, fgets, fprintf, fclose, fseek, ftell` (`vehicle.c`, `booking.c`, `billing.c`) |
| Structure | `Vehicle`, `Booking` (`common.h`), `Bill`, `Rate` |
| Array of structures | `rateTable[]`, dynamic list |
| Pointer | `calculateBill(Bill *bill, ...)`, `splitCSV()` |
| Memory | `realloc` (`growArray()`), `free()` |
| String | `strcmp, strtok, strlen, strchr, strncpy` |
| Control flow | `switch` menu, `if/else` validation |

## সীমাবদ্ধতা

- Booking করলেই গাড়ি `Rented` হয়। ভবিষ্যতের আলাদা আলাদা তারিখে একই গাড়ির একাধিক advance booking নেই।
- Password কোডের ভেতরে লেখা। এটি শুধু শেখার প্রজেক্টের জন্য।
- Text ঘরে comma (,) দেওয়া যায় না, কারণ CSV comma দিয়ে ঘর আলাদা করে।
