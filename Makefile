.PHONY: clean All

All:
	@echo "----------Building project:[ SAT - Debug ]----------"
	@cd "SAT" && "$(MAKE)" -f  "SAT.mk"
clean:
	@echo "----------Cleaning project:[ SAT - Debug ]----------"
	@cd "SAT" && "$(MAKE)" -f  "SAT.mk" clean
