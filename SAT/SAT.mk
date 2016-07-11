##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=SAT
ConfigurationName      :=Debug
WorkspacePath          := "/home/greg/SAT"
ProjectPath            := "/home/greg/SAT/SAT"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=07/11/16
CodeLitePath           :="/home/greg/.codelite"
LinkerName             :=/usr/bin/clang++
SharedObjectLinkerName :=/usr/bin/clang++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="SAT.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lgtest -lsfml-graphics -lsfml-window -lsfml-system
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/clang++
CC       := /usr/bin/clang
CXXFLAGS :=  -g -O0 -Wall -std=c++14 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/vector2.cpp$(ObjectSuffix) $(IntermediateDirectory)/projection.cpp$(ObjectSuffix) $(IntermediateDirectory)/polygon.cpp$(ObjectSuffix) $(IntermediateDirectory)/collision.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/greg/SAT/SAT/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/vector2.cpp$(ObjectSuffix): vector2.cpp $(IntermediateDirectory)/vector2.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/greg/SAT/SAT/vector2.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/vector2.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/vector2.cpp$(DependSuffix): vector2.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/vector2.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/vector2.cpp$(DependSuffix) -MM "vector2.cpp"

$(IntermediateDirectory)/vector2.cpp$(PreprocessSuffix): vector2.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/vector2.cpp$(PreprocessSuffix) "vector2.cpp"

$(IntermediateDirectory)/projection.cpp$(ObjectSuffix): projection.cpp $(IntermediateDirectory)/projection.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/greg/SAT/SAT/projection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/projection.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/projection.cpp$(DependSuffix): projection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/projection.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/projection.cpp$(DependSuffix) -MM "projection.cpp"

$(IntermediateDirectory)/projection.cpp$(PreprocessSuffix): projection.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/projection.cpp$(PreprocessSuffix) "projection.cpp"

$(IntermediateDirectory)/polygon.cpp$(ObjectSuffix): polygon.cpp $(IntermediateDirectory)/polygon.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/greg/SAT/SAT/polygon.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/polygon.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/polygon.cpp$(DependSuffix): polygon.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/polygon.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/polygon.cpp$(DependSuffix) -MM "polygon.cpp"

$(IntermediateDirectory)/polygon.cpp$(PreprocessSuffix): polygon.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/polygon.cpp$(PreprocessSuffix) "polygon.cpp"

$(IntermediateDirectory)/collision.cpp$(ObjectSuffix): collision.cpp $(IntermediateDirectory)/collision.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/greg/SAT/SAT/collision.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/collision.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/collision.cpp$(DependSuffix): collision.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/collision.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/collision.cpp$(DependSuffix) -MM "collision.cpp"

$(IntermediateDirectory)/collision.cpp$(PreprocessSuffix): collision.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/collision.cpp$(PreprocessSuffix) "collision.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


