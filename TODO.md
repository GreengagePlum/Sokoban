# TODO

## Bugs & Fixes

- [ ] fix level relative path

## Features

- [ ] Printf display method implementation to add
- [ ] Resizable SDL2 window
- [ ] Ncurses terminal window size warning
- [ ] Sound effects
- [ ] Music
- [ ] Themes (Sprites)
- [ ] Pause menu (restart, main menu, level selector)
- [ ] Game modes (story, pvp online, arcade)
- [ ] Score counter
- [ ] Move counter
- [ ] Impossibility detector
- [ ] Lives/Limited tries mode
- [ ] Chronometer/Passed time
- [ ] High scores
- [ ] Save and load game
- [ ] Ncurses colors

## Configuration

- [ ] GitLab Releases
- [ ] Cicd pages, test
- [ ] Packaging and distribution in universal formats
- [ ] uninstall script
- [ ] git release script (Python)
    - [ ] version number script
- [ ] git commit message hook
- [ ] INSTALL
- [ ] UNINSTALL
- [ ] CONTRIBUTING
- [ ] CHANGELOG
- [ ] Bin folder for executable
- [ ] Archive folder for archive ? (maybe)
- [ ] Dynamic debug compilation in makefile (by passing in argument when calling make CFLAGS=-g)

## Miscellaneous

- [ ] Reddit post

## Done

- [x] Doxygen depends on source and header files
    - [x] Centralize sources and objects instead of test_sources and main_sources so on (depending on make variable given) (this could make makefile simpler and make it easier to implement doxygen which depends on sources and headers where i won’t need to create multiple doxygen targets for different scenarios. One with dynamic variable will suffice)
- [x] Add homebrew gcc version to README
- [x] LICENCE
- [x] System SDL2 installation
- [x] TODO
- [x] gcc -std=cXX (specify C standard)
