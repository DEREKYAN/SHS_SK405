# Platform-M3:
#1, Sep.24, 2015  SK3XX project source codes, now debugging, still have not released any version.

#2, Sep.29, PM 3:20 Finished codes notes, next job is Optimization codes 

#3, Sep.29, PM 5:00 source codes are optimizated with the highest level of size. Now application source codes size is 0x3B54,  it's enough for us. 
    
#4, Oct.8 Trim RTC timer base on LSI clock with HSI clock ( HSI 1% error, LSI 30KHZ~50KHZ )

#5, Oct.9 start watchdog, watchdog will overflow after 26 seconds without clearing watchdog counter, and system will reset.

#6, Oct.12  Modify indicttion LED shedule according hardware A08 and new machine. Enable Watchdog after TRIM
   
#7, Oct.13  Upload Angaza_PAYG_Library_1_8_15 to github.

#8, Oct.15  Upload NV flash codes to github

#9, Oct.20  Build folder of project, Move *.c and *.h to different folder 

#10. Oct.21 Merge Angaza_PAYG_Library_1_10_17 to github

#11. Oct.23 Implement PAYG keycode.

#12. Oct.29 Build commnication between phone and M3 platform with cable 

#13. Nov.2 Implement PAYG cable communication 

#14. Nov.2 Implement serial command 

#15. Nov.5 Implement low power

#16.  Nov.6 Release V0.0 

#17. Nov.9 Issue A1 - LED Current is a little higher than the specs

#18. Nov.9 Issue A5 - Fuel indicator issue for Low Fuel mode/ Low Fuel

#19. Nov.10 Issue A7 - Fuel gauge value will keeps 399, rather than 0 after system has been triggered into Empty Fuel mode by voltage threshold

#20. Nov.10 Fix the bug of FLASH operation 

#21. Nov.10 Modify made date according to Year and days 

#22. Nov.16 Modify bootloader protocol for try-made

#23. Nov.16 Turn on charging level 1 LED 

#24. Nov.16 Release V0.1

#25. Nov.19 Low battery is triggered by error in PP

#26. Nov.19 Solve To-Do-List A19

#27. Nov.19 Solve To-Do-List A27 

#28. Nov.20 Solve To-Do-List A32

#29. Nov.20 Release V0.3

#30. Nov.26 UART data logging communication specification according to V6.4F

#31. Nov.29 Release V0.4 

#32. Dec.2 Solve A35,A12,A15,A18,A31,A37,A38,A39 from To-do-list, verifi them wiht version V04A 

#33. Dec.2 Increase lantern current @Mode 1 and 2

#34. Dec.2 Fix A36 From To-do-list 

#35. Dec.2 Change enter sleep mode times

#36. Dec.3 Fix A31,A35,A40,A41,A42,A43 from To-do-List

#37. Dec.4 Release V0.4C for test

#38. Dec.4 Update PAYG library with Angaza_PAYG_Library_1_16_23

#39. Dec.4 Fix A35,A42 from To-Do-List

#40. Dec.4 Upate PAYG library with Angaza_PAYG_Library_1_17_24

#41. Dec.4 Release V0.4D for test 

#42. Dec.7 Update current threshold to verify A17, A18 from To-Do-List

#43. Dec.7 Implement Cable communication according to Usage Data For Angaza -V4.7A

#44. Release V0.4G to verify the funcitons

#45. Change PAYG indication according BRYAN's requirement 

#46. Release V0.4H to verify PAYG indication

#47. Dec.8 Optimze codes to release FLASH ROM size 

#48. Dec.8 Update PAYG library with Angaza_PAYG_Library_1_19_26

#49. Dec.8 Release V0.4J to verify software 

#50. Dec.9 Fix RTC time fault

#51. Dec.9 Fix wake_up without any cause 

#52. Dec.9 Release V0.4K

#53. Dec.10 Fix nonvolatile storage has not been functioning correctly

#54. Dec.11 Update feedback display

#55. Dec.12 Lamp mode loop from mode off, mode 1, mode 2 and mode 3 at credit NEAR_DISABLED status

#56. Release SK312_V0.4L

#57. Fix A17 - Fuel indicator flash periodically during sitting

#58. Release SK312_V0.4M

#59. Fix A17, A18, A35 from To-do-List

#60. Release V0.5 

#61. Fix To-do-list A47 and release V0.5A

#62. Update according to Anagaza library Angaza_PAYG_Library_1_21_28

#63. Optimization RTC register configure 

#64. Release V0.5G