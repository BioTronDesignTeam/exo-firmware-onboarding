# Git Installation & Setup Guide (Firmware Onboarding)

This guide will get you set up with Git and give you access to the firmware repository used by the team.

---

## 1. What is Git?

Git is a **version control system** used to track changes in code and collaborate with other developers.

We use Git to:

- Keep a history of all code changes.
- Work on features without overwriting each other's work.
- Review code through Pull Requests (PRs).
- Sync your local code with the team's repository on GitHub.

> You'll use Git every day during firmware development.

---

## 2. Install Git

Choose the instructions for your operating system.

### Windows

1. Download and install **Git for Windows**.
2. Run the installer.
3. Keep all installation options as **Default**.
4. Open **Git Bash** after installation.

Verify the installation:

```bash
git --version
```

### Ubuntu (Recommended)

```bash
sudo apt update
sudo apt install git
```

Verify the installation:

```bash
git --version
```

### macOS

Using Homebrew:

```bash
brew install git
```

Or install Apple's Command Line Tools:

```bash
xcode-select --install
```

Verify:

```bash
git --version
```

---

## 3. Request Access to Our Repository

Before cloning the repository, you need access to the team's GitHub repository.

### Steps

1. Create or sign in to your GitHub account.
2. Ping a software lead on **Discord** with your GitHub username.

Example message:

```text
Hi! Could I get access to the firmware GitHub repository?

GitHub username: your-github-username
```

Wait until you've been added to the repository before continuing.

---

## 4. Configure Git

Set your Git identity once after installation.

Use the same email associated with your GitHub account.

```bash
git config --global user.name "Your Name"
git config --global user.email "your_email@example.com"
```

Example:

```bash
git config --global user.name "Jane Doe"
git config --global user.email "janedoe@gmail.com"
```

Verify your configuration:

```bash
git config --global --list
```

Expected output:

```text
user.name=Jane Doe
user.email=janedoe@gmail.com
```

---

## 5. Configure GitHub Authentication (SSH)

We use **SSH authentication** so you won't need to enter your GitHub credentials every time.

### Generate an SSH key

```bash
ssh-keygen -t ed25519 -C "your_email@example.com"
```

Press **Enter** through the prompts to use the default save location.

### Start the SSH agent

```bash
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_ed25519
```

### Copy your public key

```bash
cat ~/.ssh/id_ed25519.pub
```

Copy the entire output.

### Add the key to GitHub

1. Go to **GitHub → Settings**.
2. Open **SSH and GPG Keys**.
3. Click **New SSH Key**.
4. Paste your public key and save.

### Test the connection

```bash
ssh -T git@github.com
```

Expected output:

```text
Hi your-username! You've successfully authenticated...
```

---

## 6. Clone the Repository

After you've been granted access:

```bash
git clone https://github.com/BioTronDesignTeam/exo-firmware-onboarding.git
```

Move into the repository:

```bash
cd exo-firmware-onboarding
```

---

## 7. Verify Everything Works

Check that the remote repository is configured:

```bash
git remote -v
```

You should see both **fetch** and **push** remotes pointing to the team's GitHub repository.

Check your current branch:

```bash
git branch
```

You should be on the default branch (`main`).
