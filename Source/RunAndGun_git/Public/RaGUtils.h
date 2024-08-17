#pragma once

class RaGUtils
{
public:
	template<typename T>
    static T* GetRaGPlayerComponent(AActor* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }
};