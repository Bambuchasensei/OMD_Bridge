# OMD Bridge

Мост между медициной **Terje** и системой боли/конечностей **Inedia** для сервера One More DayZ, с новыми конечностями «кисти» и «стопы».

![Version](https://img.shields.io/badge/version-0.1.0-blue)
![Status](https://img.shields.io/badge/status-in%20development-orange)
![Enforce Script](https://img.shields.io/badge/language-Enforce%20Script-blue)

> **TL;DR (EN):** A compatibility bridge for DayZ that connects Inedia's limb/pain system with Terje Medicine & Skills and the other OMD mods. It adds two new limbs to Inedia — **hands** and **feet** — with treatment actions (bandaging, suturing, bullet extraction, fracture stabilization, disinfection) and HUD badges. Client mod + closed-source server part. Written in Enforce Script.

## Возможности

- **Новые конечности для Inedia — кисти и стопы.** Для них работают медицинские действия: перевязка глубоких ран (лёгких, средних, тяжёлых), зашивание, снятие повязок, извлечение пули, фиксация и снятие фиксации переломов.
- **Обработка мелких ран и швов:** перевязка царапин, перевязка и замена грязной повязки на швах, дезинфекция швов — для головы, торса, рук, кистей, ног и стоп. Действия доступны на себе и на другом игроке.
- **Согласование Inedia и Terje:** связка боли Inedia с медициной и навыками Terje (обезболивающие, лечение, кровотечения, дебаффы от боли, ограничения действий).
- **Настройка медицинских предметов** (шина, набор для шины, швейный набор и др.) под новые конечности.
- **HUD:** иконки состояния кистей, стоп, рук и ног и оверлей царапин.

## В разработке

- Самостоятельно зажившая рана превращается в шов.
- Гемостатик Terje для глубоких ран.
- Стрелки на HUD для глубоких ран на кистях и стопах.

## Требования

- DayZ (клиент и сервер)
- Inedia Infected AI (`InediaInfectedAI`)
- Terje: `TerjeCore`, `TerjeMedicine`, `TerjeMedicine_Tools`, `TerjeSkills`

## Архитектура

Мод состоит из двух частей:

- **клиентская часть** (этот репозиторий) — подключается через `-mod=` на клиенте и сервере;
- **серверная часть** `OMD_Bridge_Server` — подключается на сервере через `-serverMod=`. Исходники серверной части закрыты.

Серверная часть обязательна: без неё мод работает некорректно.

## Установка

1. Подпишитесь на зависимости (Inedia, Terje) и на этот мод.
2. Добавьте `OMD_Bridge` в `-mod=` клиента и сервера **после** Inedia и Terje.
3. Добавьте `OMD_Bridge_Server` в `-serverMod=` сервера.

## Конфигурация

При первом запуске создаётся файл `omd/OMD_Bridge.json` в папке профиля сервера (обезболивающие, лечение и т. п.). Изменения применяются после перезапуска сервера.

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

## Авторы

- **Comrad-Sensei** ([Bambuchasensei](https://github.com/Bambuchasensei))
- **mmetrjuk**

Сообщество и сервер **One More DayZ (OMD)**.

Thanks to Inedia and Terje.

## Лицензия

All rights reserved. Код и ассеты опубликованы для ознакомления (портфолио). Использование, копирование и перезалив — только с разрешения авторов.