
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

UCLASS()
class SLASH_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Same name will link with the other variable
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
};
