## ⚙️ Step 1. Save your script

Put your script in your project root as:

```
run.sh
```

Make sure it’s executable:

```bash
chmod +x run.sh
```

---

## ⚙️ Step 2. Create a VS Code Task

1. Open **Command Palette** → `Ctrl + Shift + P`
2. Type **“Tasks: Configure Task” → Create tasks.json file from template → Others**

This creates a `.vscode/tasks.json` file.

Replace its content with:

```json
{
  "version": "2.0.0",
  "tasks": [
    {
      "label": "Run RayCraft",
      "type": "shell",
      "command": "./run.sh",
      "group": {
        "kind": "build",
        "isDefault": true
      },
      "problemMatcher": [],
      "presentation": {
        "reveal": "always",
        "panel": "shared"
      }
    }
  ]
}
```

---

## ⚙️ Step 3. Bind it to a key

Open **Command Palette** again → search for **“Open Keyboard Shortcuts (JSON)”**.

Then add this entry inside the array:

```json
{
  "key": "ctrl+shift+b",
  "command": "workbench.action.tasks.runTask",
  "args": "Run RayCraft"
}
```

Now pressing **Ctrl + Shift + B** will automatically:

1. Compile your code
2. Run the raytracer
3. Open the generated image in IrfanView 🎨

---

## ⚙️ Step 4. Windows-specific tip

If your VS Code terminal is **PowerShell or CMD**, it might not recognize `./run.sh`.
In that case, change the `command` in `tasks.json` to:

```json
"command": "bash run.sh"
```

And make sure you have **Git Bash** installed (which you already do).

---

✅ **Final Flow**
Press **Ctrl + Shift + B** → you’ll see:

```
🔧 Compiling...
🎯 Running ray tracer...
🖼️ Opening in IrfanView...
```

and your rendered `output.ppm` opens automatically.
