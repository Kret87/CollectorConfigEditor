let currentConfig = null;

async function loadConfig()
{
    const endpointList = document.getElementById("endpointList");

    try
    {
        const response = await fetch("/api/config");

        if (!response.ok)
            throw new Error("Nie udało się pobrać konfiguracji.");

        currentConfig = await response.json();

        endpointList.replaceChildren();

        if (currentConfig.endpoints.length === 0)
        {
            endpointList.textContent = "Brak endpointów.";
            return;
        }

        for (const endpoint of currentConfig.endpoints)
        {
            const item = document.createElement("div");

            item.textContent =
                endpoint.description +
                " | " +
                endpoint.url +
                " | interwał: " +
                endpoint.interval_ms +
                " ms | " +
                (endpoint.enabled ? "włączony" : "wyłączony");

            endpointList.appendChild(item);
        }
    }
    catch (error)
    {
        endpointList.textContent = "Błąd: " + error.message;
    }
}

async function saveConfig()
{
    const statusMessage = document.getElementById("statusMessage");

    if (currentConfig === null)
    {
        statusMessage.textContent = "Najpierw wczytaj konfigurację.";
        return;
    }

    statusMessage.textContent = "Zapisywanie...";

    try
    {
        const response = await fetch("/api/config",
        {
            method: "POST",
            headers:
            {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(currentConfig)
        });

        if (!response.ok)
            throw new Error("Nie udało się zapisać konfiguracji.");

        await response.json();

        statusMessage.textContent = "Konfiguracja zapisana.";
    }
    catch (error)
    {
        statusMessage.textContent = "Błąd: " + error.message;
    }
}

document
    .getElementById("loadButton")
    .addEventListener("click", loadConfig);

document
    .getElementById("saveButton")
    .addEventListener("click", saveConfig);

loadConfig();