# টিমের GitHub কাজের গাইড

`main` → প্রত্যেকের আলাদা branch → Pull Request → `main`

Branch: `feature/vehicle`, `feature/booking`, `feature/rental`, `feature/billing`

দুটি zip আছে:
- **team-starter**: common ফাইল সম্পূর্ণ, ৪টি মডিউল খালি (stub)। এটি `main`-এ যাবে।
- **vehicle-rental-system**: সম্পূর্ণ কোড। এখান থেকে প্রত্যেকে নিজের `.c` ফাইল নেবে।

## ধাপ ১: একজন (leader) main তৈরি করবে

GitHub-এ খালি repository বানান (README ছাড়া)। team-starter ফোল্ডার VS Code-এ খুলে:

    git init
    git add .
    git commit -m "Add project structure and common files"
    git branch -M main
    git remote add origin <repo-url>
    git push -u origin main

তারপর GitHub → Settings → Collaborators থেকে বাকি ৩ জনকে যোগ করুন। তারা invitation accept করবে।
আগে থেকেই repo-তে কিছু থাকলে এই ধাপ হুবহু চালাবেন না। repo clone করে তার ভেতরে starter ফাইল কপি করুন।

## ধাপ ২: প্রত্যেকে নিজের branch-এ কাজ করবে

    git clone <repo-url>
    cd <repo-name>
    git switch -c feature/billing

(leader আবার clone করবে না; নিজের ফোল্ডারেই branch বানাবে।)

সম্পূর্ণ কোড থেকে শুধু নিজের `.c` ফাইল `src` ফোল্ডারে কপি করে পুরোনোটি replace করুন। `.\run.bat` দিয়ে চালিয়ে দেখুন। তারপর:

    git restore data/
    git status
    git add src/billing.c
    git commit -m "Add billing and cost calculation module"
    git push -u origin feature/billing

`git restore data/` টেস্ট করার সময় বদলে যাওয়া CSV আগের অবস্থায় ফেরায়। এতে conflict এড়ানো যায়।

| সদস্য | ফাইল | Branch |
|---|---|---|
| ১ | `src/vehicle.c` | `feature/vehicle` |
| ২ | `src/booking.c` | `feature/booking` |
| ৩ | `src/rental.c` | `feature/rental` |
| ৪ | `src/billing.c` | `feature/billing` |

প্রত্যেকে **নিজের GitHub account ও নিজের git নাম/email** থেকে commit-push করবে:

    git config user.name "আপনার নাম"
    git config user.email "আপনার-github-email"

## ধাপ ৩: Pull Request

GitHub → **Compare & pull request** → base: `main`, compare: নিজের branch → Create। অন্য একজন কোড দেখে **Merge** করবে।

সহজ ক্রম: billing → vehicle → booking → rental। Stub থাকায় যেকোনো ক্রমে compile হবে, তবে পুরো feature কাজ করবে ৪টি merge হওয়ার পর।

## ধাপ ৪: সব merge-এর পর

    git switch main
    git pull
    .\run.bat

## পরামর্শ

নিজের মডিউল ভালোভাবে পড়ুন ও বুঝুন, কারণ viva-তে প্রশ্ন হবে। বোঝার পর ছোট পরিবর্তন (যেমন message বা rate) করলে আলাদা commit করুন। এতে প্রকৃত কাজের history থাকবে।
