# 🚪 Door Quest
> A game with simple Doors and Keys mechanics, made as training for Unreal 5.4

## ✨ Features
- Multiple types of pickable items (Keys, Jewels and Coins)
- Inventory UI of items being carried at the top left
- Multiple types of Doors (Hinge, Sliding, Automatic, Locked that shows necessary items in order to open it)
- Input Action indicators for Door Interaction and Item Pickup
- A Puzzle Level that uses the mechanics mentioned above

## 🏗️ Architecture / Final Thoughts
- Focus on not having an extensive Blueprint hierarchy and more on Reusable Code, Components and Composition
- Played around with the use of Child Actors, but didn't find them to be very ergonomic, and sometimes they didn't update properly when the source Blueprint was modified
- Interface usage and interoperability between C++ and Blueprints is great!
- Found a lack of practicality with 3D Model animation in Editor, when making doors open the only good option I've found was to use Timelines and then bind to some Rotation / Location change logic. UMG Animations are great in the other hand, although not reusable
- The Viewmodel plugin is still in beta, the Editor crashed numerous times during its usage when binding things up, and sometimes types are converted to "HOTRELOAD" versions that require an Editor restart to go back to normal

## 📷 In-game Recordings!
### 👶 Initial Stage / Prototyping
https://github.com/user-attachments/assets/5ebf9166-c1ec-4a8e-a01f-e2f79f903cc3

<br>

### 🔑 Level 1

<details>
  <summary><h4>💡 Solution 1 (SPOILER)</h4></summary>
  
  https://github.com/user-attachments/assets/d37ad33b-f5fd-464a-a92c-49564808fa51
</details>
<details>
  <summary><h4>💡 Solution 2 (SPOILER)</h4></summary>

  https://github.com/user-attachments/assets/f38faba5-df18-49ab-be58-c2ba6492ad11
</details>
