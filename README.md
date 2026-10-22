# OMD Bridge

Мост между медициной **Terje** и системой боли/конечностей **Inedia** для сервера One More DayZ, с новыми конечностями «кисти» и «стопы».

![DayZ](https://img.shields.io/badge/DayZ-1.2x-red)
![Enforce Script](https://img.shields.io/badge/language-Enforce%20Script-blue)
![Status](https://img.shields.io/badge/status-in%20development-orange)

> **TL;DR (EN):** A compatibility bridge for DayZ that connects Inedia's limb/pain system with Terje Medicine & Skills and the other OMD mods. It adds two new limbs to Inedia — **hands** and **feet** — with full treatment actions (bandaging, suturing, bullet extraction, fracture stabilization, disinfection) and HUD badges. Written in Enforce Script.

## Возможности

- **Новые конечности для Inedia — кисти и стопы.** Для них работают те же медицинские действия, что и для остальных частей тела: перевязка глубоких ран (лёгких, средних, тяжёлых), зашивание, снятие повязок, извлечение пули, фиксация и снятие фиксации переломов.
- **Обработка мелких ран и швов:** перевязка царапин, перевязка и замена грязной повязки на швах, дезинфекция швов — для головы, торса, рук, кистей, ног и стоп. Действия доступны на себе и на другом игроке.
- **Согласование Inedia и Terje:** связка боли Inedia с медициной и навыками Terje (обезболивающие, лечение, кровотечения, дебаффы от боли, ограничения действий).
- **Настройка медицинских предметов** (шина, набор для шины, швейный набор и др.) под новые конечности через конфиг Inedia.
- **HUD:** иконки состояния кистей, стоп, рук и ног и оверлей царапин.

## Требования

- DayZ (клиент и сервер)
- [Inedia Infected AI](https://steamcommunity.com/workshop/) — `InediaInfectedAI`
- Terje: `TerjeCore`, `TerjeMedicine`, `TerjeMedicine_Tools`, `TerjeSkills`

## Установка

1. Подпишитесь на зависимости (Inedia, Terje) и на этот мод.
2. Добавьте мод в `-mod=` клиента и сервера **после** Inedia и Terje.
3. Серверная логика вынесена в отдельный приватный репозиторий (`OMD_Bridge_Server`) и ставится только на сервер.

## Конфигурация

При первом запуске создаётся JSON-файл `%profile%/omd/OMD_Bridge.json` с настройками моста (обезболивающие, лечение и т. п.). Изменения применяются после перезапуска сервера.

## Структура проекта

```
OMD_Bridge/
├── config.cpp          # CfgPatches, CfgMods, параметры предметов для Inedia
├── mod.cpp
├── stringtable.csv     # локализация действий
├── gui/                # иконки и layout для HUD
└── Scripts/
    ├── 3_Game/         # конфиг (JSON) и типы
    ├── 4_World/        # действия лечения, боль, кровотечения, навыки
    └── 5_Mission/      # HUD
```

## Скриншоты

<!-- TODO: добавить скриншоты (docs/images/...) -->
_Скоро._

## Steam Workshop

<!-- TODO: ссылка на мастерскую Steam -->
_Мод пока не опубликован в мастерской._

## Автор

**Bambuchasensei** — разработка и дизайн механик для сообщества и сервера **One More DayZ (OMD)**.

## Лицензия

All rights reserved. Код и ассеты опубликованы для ознакомления (портфолио). Использование, копирование и перезалив — только с разрешения автора.